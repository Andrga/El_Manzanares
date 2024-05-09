//---------------------------------------------------------------------------
#include "PixMap32RGBA.h"
#include <fstream>
#include <exception>
//using namespace std;
//---------------------------------------------------------------------------

// cabeceras del archivo bmp
// tipo y valores para nuestro caso: bmp en modo bgr de 24 bits con los pixeles por filas bottom to top y columnas left to right
struct bitmap_file_header  
{ 
  /*WORD*/  unsigned short signature;  // 'BM'
  /*DWORD*/ unsigned int   size_file;  // unreliable ->  = (offset_map + size_map) bytes 
  /*WORD*/  unsigned short reserved1;  // 0
  /*WORD*/  unsigned short reserved2;  // 0
  /*DWORD*/ unsigned int   offset_map; // 54 (14 fileheader + 40 information_header) bytes 
};

struct bitmap_information_header
{
  /*DWORD*/ unsigned int size_info_header;  // 40 bytes = sizeof(bitmap_information_header)
  /*LONG*/  int width;  // columns (left to right order)
  /*LONG*/  int height; // rows (bottom to top order)
  /*WORD*/  unsigned short planes;  // 1 color planes 
  /*WORD*/  unsigned short bits_per_pixel;  // 24 bits -> 3(BGR) bytes
  /*DWORD*/ unsigned int compression;   // 0 = BI_RGB, no pixel array compression used
  /*DWORD*/ unsigned int size_map;   // (width * 3 + pading) * height  bytes
  /*LONG*/  int x_prpm;  // (Print resolution pixels/meter horizontal) unreliable
  /*LONG*/  int y_prpm;  // (Print resolution pixels/meter vertical) unreliable 
  /*DWORD*/ unsigned int clr_used;  // 0 (Number of colors in the palette)
  /*DWORD*/ unsigned int clr_important;   // 0 (means all colors are important)
};
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::load_headers(std::ifstream & stream,  unsigned int & width, unsigned int & height) const// throw(std::ios_base::failure);
{
      width = 0; height = 0;
      bitmap_file_header bfh;
      bitmap_information_header bih; 
      stream.read(reinterpret_cast<char*>(&bfh.signature), 2); 
      stream.read(reinterpret_cast<char*>(&bfh.size_file), 4); 
      stream.read(reinterpret_cast<char*>(&bfh.reserved1), 2); 
      stream.read(reinterpret_cast<char*>(&bfh.reserved2), 2); 
      stream.read(reinterpret_cast<char*>(&bfh.offset_map),4); 
      
      stream.read(reinterpret_cast<char*>(&bih), 40);   
      width = bih.width; 
      height = bih.height;

      if (bfh.signature != 0x4D42) // 'BM' 
      {
         throw std::ios_base::failure("PixMapRGBA::load_bmpBGR() ERROR: Invalid signature value");
      }
      if (bih.bits_per_pixel != 24)   // 3(BGR) bytes
      {
         throw std::ios_base::failure("PixMapRGBA::load_bmpBGR() ERROR: Invalid depth color (bits per pixel)");
      }
      if (bih.size_info_header != 40)   // size_of(bitmap_information_header)
      {
         throw std::ios_base::failure("PixMapRGBA::load_bmpBGR() ERROR: Invalid size information header");
      }
      if(bih.clr_used != 0) // color palette
      {
        throw std::ios_base::failure("PixMapRGBA::load_bmpBGR() ERROR: Invalid number of colors in the palette");
      }
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::save_headers(std::ofstream & stream) const noexcept
{
      bitmap_file_header bfh;
      bitmap_information_header bih;

      bih.size_info_header = 40;  // sizeof(bitmap_information_header) 
      bih.width            = width_;
      bih.height           = height_;
      bih.planes           =  1;  // color planes
      bih.bits_per_pixel   = 24;  // 3(BGR) bytes
      bih.compression      =  0;  // BI_RGB
      bih.size_map         = ((bih.width * 3) + ((4 - ((3 * width_) % 4)) % 4)) * bih.height; 
      bih.x_prpm           =  0;  //  Print resolution 2835 = 72 dpi × 39.3701 inches per meter yields 2834.6472
      bih.y_prpm           =  0;  //  Print resolution 2835 = 72 dpi × 39.3701 inches per meter yields 2834.6472
      bih.clr_used         =  0;
      bih.clr_important    =  0;
                                       
      bfh.signature   = 0x4D42;  // 'BM'    
      bfh.size_file   = 54 + bih.size_map; // offset_map + size_map      
      bfh.reserved1   = 0;
      bfh.reserved2   = 0;
      bfh.offset_map  = 54;       

      stream.write(reinterpret_cast<const char*>(&bfh.signature), 2); 
      stream.write(reinterpret_cast<const char*>(&bfh.size_file), 4); 
      stream.write(reinterpret_cast<const char*>(&bfh.reserved1), 2); 
      stream.write(reinterpret_cast<const char*>(&bfh.reserved2), 2); 
      stream.write(reinterpret_cast<const char*>(&bfh.offset_map),4); 

      stream.write(reinterpret_cast<const char*>(&bih), 40);  
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

PixMap32RGBA::PixMap32RGBA(PixMap32RGBA && pixmap) noexcept
	: data_{ pixmap.data_ }, width_{ pixmap.width_ }, height_{ pixmap.height_ }
{
	pixmap.data_ = nullptr;
	pixmap.height_ = 0;
	pixmap.width_ = 0;
}
//-------------------------------------------------------------------------------------------

PixMap32RGBA & PixMap32RGBA::operator=(PixMap32RGBA && pixmap) noexcept
{
	if (this != &pixmap)
	{
		delete[] data_;
		data_ = pixmap.data_;
		width_ = pixmap.width_;
		height_ = pixmap.height_;
		pixmap.data_ = nullptr;
		pixmap.width_ = 0;
		pixmap.height_ = 0;
	}

	return *this;
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::free() noexcept
{
   delete[] data_;
   data_ = nullptr;
   width_ = 0;
   height_ = 0;
}
//-------------------------------------------------------------------------------------------
PixMap32RGBA PixMap32RGBA::clone()  // throw(std::exception, std::bad_alloc)
{
	PixMap32RGBA clon;
	clon.reserve(width(), height());
	
	for (GLsizei i = 0; i< width_ * height_; i++)
		clon.data_[i] = data_[i];

	return clon;
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::reserve(GLsizei width, GLsizei height) // throw(std::exception, std::bad_alloc)
{
  if(width > width_ || height > height_) 
    {  
      try
      {  
         auto aux = new rgba_color [width * height];  
		 if (aux == nullptr) throw std::bad_alloc();
         
		 for (GLsizei i = 0; i< width_ * height_; i++)
			 aux[i] = data_[i];

		 delete [] data_;
		 data_ = aux;
		 width_ = width;
		 height_ = height;
      }
      catch(std::bad_alloc &) 
	  {
        throw std::exception("PixMap32RGBA::reserve() ERROR: Could not allocate memory (bad_alloc)"); 
      }
  }   
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::load_bmp24BGR(const std::string & file_name) // throw(std::ios_base::failure, std::bad_alloc)
{
      std::ifstream stream(file_name.c_str(), std::ios::binary);
      stream.exceptions( std::ifstream::failbit | std::ifstream::badbit );
      if (!stream.is_open()) throw std::ios_base::failure("PixMap32RGBA::load_bmpBGR() ERROR: Could not open file");
      
      unsigned int width, height;
      load_headers(stream, width, height);

      //GLsizei Bytes_Per_Pixel = 3;
      unsigned int padding = (4 - ((3 * width) % 4)) % 4;     
      unsigned int rowSize = width * 3 + padding; 

	  reserve(width, height);
      char* rowAux = new char [rowSize];  // GLubyte

	  for (GLsizei i = 0; i < height_; ++i)
      {
         stream.read(rowAux,  rowSize); 
         row_bgr_rgba(rowAux, i);  
      }

      stream.close();
      delete [] rowAux;
} 
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::row_bgr_rgba(char* rowAux, unsigned int r) noexcept
{
   unsigned int j =  0, f = r* width_ + width_;  

   for (unsigned int i = r* width_; i <  f; i++)
   {
     data_[i].b = rowAux[j++];
     data_[i].g = rowAux[j++];
     data_[i].r = rowAux[j++];
     data_[i].a = 255;
   }
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::row_rgba_bgr(char* rowAux, unsigned int r) const noexcept
{
   unsigned int j =  0, f = r* width_ + width_;  

   for (unsigned int i = r* width_; i <  f; i++)
   {
      rowAux[j++] = data_[i].b;
      rowAux[j++] = data_[i].g;
      rowAux[j++] = data_[i].r;
   }
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::save_bmp24BGR(const std::string& file_name) const  // throw(std::ios_base::failure)
{
      std::ofstream stream(file_name.c_str(),std::ios::binary);
      stream.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
      if (!stream.is_open())  throw std::ios_base::failure("PixMap32RGB::save_bmpBGR() ERROR: Could not open file"); 
   
      save_headers(stream);
      //GLsizei Bytes_Per_Pixel = 3;
      unsigned int padding = (4 - ((3 * width_) % 4)) % 4;   
      unsigned int rowSize = width_ * 3 + padding;  
     
      char* rowAux = new char [rowSize];  // GLubyte

      for (GLsizei i = 0; i < height_; ++i)
      {  
        row_rgba_bgr(rowAux,i);  
        stream.write(rowAux, rowSize);
      }

      delete [] rowAux;
      stream.close();
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::set_alpha(GLubyte alpha) noexcept
{
    //if(data_ != nullptr) 
	  for (GLsizei i = 0; i< width_ * height_; i++)
        data_[i].a = alpha;    
}
//-------------------------------------------------------------------------------------------

void PixMap32RGBA::set_colorkey_alpha(glm::u8vec3 colorKey, GLubyte alpha ) noexcept
{
	//if (data_ != nullptr) 
	  for (GLsizei i = 0; i< width_ * height_; i++)
	  {
        if (data_[i].r == colorKey.r && data_[i].g == colorKey.g && data_[i].b == colorKey.b)
            data_[i].a = alpha;
	  }
}
//-------------------------------------------------------------------------------------------
