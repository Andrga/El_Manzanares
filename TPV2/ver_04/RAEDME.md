# PingPong v4

This version uses a simple concept of components to change the behavior of the paddles/ball. We define a 3 kinds of component interfaces (Input, Render and Physics) and a corresponding class Container that inherits from GameObject and includes vectors of such components (it is like an entity). 

When calling hanldeInput/update/render of a container it simply calls  the ones of the corresponding components. 

