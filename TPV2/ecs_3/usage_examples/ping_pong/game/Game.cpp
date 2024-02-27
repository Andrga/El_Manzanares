// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/BounceOnBorders.h"
#include "../components/GameInfoMsgs.h"
#include "../components/GameState.h"
#include "../components/Image.h"
#include "../components/PaddleAICtrl.h"
#include "../components/PaddleKBCtrl.h"
#include "../components/PaddleMouseCtrl.h"
#include "../components/RectangleViewer.h"
#include "../components/StopOnBorders.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
		mngr_(nullptr), //
		ballTr_(nullptr), //
		gameState_(nullptr) {
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// Initialize the SDLUtils singleton
	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	sdlutils().hideCursor();

	// Create the manager
	mngr_ = new Manager();

	// create the ball entity
	//
	auto ball = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::BALL, ball);

	ballTr_ = mngr_->addComponent<Transform>(ball);
	auto ballSize = 15.0f;
	auto ballX = (sdlutils().width() - ballSize) / 2.0f;
	auto ballY = (sdlutils().height() - ballSize) / 2.0f;
	ballTr_->init(Vector2D(ballX, ballY), Vector2D(), ballSize, ballSize, 0.0f);

	mngr_->addComponent<Image>(ball, &sdlutils().images().at("tennis_ball"));
	mngr_->addComponent<BounceOnBorders>(ball);

	// create the left paddle
	auto leftPaddle = mngr_->addEntity(ecs::grp::PADDLES);

	auto leftPaddleTr = mngr_->addComponent<Transform>(leftPaddle);
	auto leftPaddleWidth = 10.0f;
	auto leftPaddleHeight = 50.0f;
	auto leftPaddleX = 5.f;
	auto leftPaddleY = (sdlutils().height() - leftPaddleHeight) / 2.0f;
	leftPaddleTr->init(Vector2D(leftPaddleX, leftPaddleY), Vector2D(),
			leftPaddleWidth, leftPaddleHeight, 0.0f);

	mngr_->addComponent<StopOnBorders>(leftPaddle);
	mngr_->addComponent<RectangleViewer>(leftPaddle,
			build_sdlcolor(0xff0000ff));
//	mngr_->addComponent<PaddleKBCtrl>(leftPaddle);
//	mngr_->addComponent<PaddleMouseCtrl>(leftPaddle);
	mngr_->addComponent<PaddleAICtrl>(leftPaddle);

	// create the right paddle
	auto rightPaddle = mngr_->addEntity(ecs::grp::PADDLES);

	auto rightPaddleTr = mngr_->addComponent<Transform>(rightPaddle);
	auto rightPaddleWidth = 10.0f;
	auto rightPaddleHeight = 50.0f;
	auto rightPaddleX = sdlutils().width() - rightPaddleWidth - 5.0f;
	auto rightPaddleY = (sdlutils().height() - rightPaddleHeight) / 2.0f;
	rightPaddleTr->init(Vector2D(rightPaddleX, rightPaddleY), Vector2D(),
			rightPaddleWidth, rightPaddleHeight, 0.0f);

	mngr_->addComponent<StopOnBorders>(rightPaddle);
	mngr_->addComponent<RectangleViewer>(rightPaddle,
			build_sdlcolor(0x00ff00ff));

//	mngr_->addComponent<PaddleKBCtrl>(rightPaddle);
	mngr_->addComponent<PaddleMouseCtrl>(rightPaddle);
//	mngr_->addComponent<PaddleAICtrl>(rightPaddle);

	// create game control entity
	auto gameCtrl = mngr_->addEntity();
	gameState_ = mngr_->addComponent<GameState>(gameCtrl);
	mngr_->addComponent<GameInfoMsgs>(gameCtrl);

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		checkCollisions();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() {
	if (gameState_->getState() != GameState::RUNNING)
		return;

	bool ballCollidesWithPaddle = false;

	auto &ballPos = ballTr_->getPos();
	auto ballWidth = ballTr_->getWidth();
	auto ballHeight = ballTr_->getHeight();

	for (auto e : mngr_->getEntities(ecs::grp::PADDLES)) {
		auto paddleTr_ = mngr_->getComponent<Transform>(e);
		ballCollidesWithPaddle = Collisions::collides(paddleTr_->getPos(),
				paddleTr_->getWidth(), paddleTr_->getHeight(), ballPos,
				ballWidth, ballHeight);

		if (ballCollidesWithPaddle)
			break;
	}

	if (ballCollidesWithPaddle) {

		// change the direction of the ball, and increment the speed
		auto &vel = ballTr_->getVel(); // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (ballTr_->getPos().getX() < 0)
		gameState_->onBallExit(GameState::LEFT);
	else if (ballTr_->getPos().getX() + ballTr_->getWidth()
			> sdlutils().width())
		gameState_->onBallExit(GameState::RIGHT);

}
