// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

#include "Container.h"
#include "GameManager.h"
#include "AIPaddle.h"
#include "BounceOnBorder.h"
#include "EmptyRectangleRenderer.h"
#include "GameCtrl.h"
#include "ImageRenderer.h"
#include "InfoMsgs.h"
#include "MovePaddleWithKeyBoard.h"
#include "MovePaddleWithMouse.h"
#include "RectangleRenderer.h"
#include "ScoreRenderer.h"
#include "SimpleMove.h"
#include "StopOnBorder.h"

Game::Game() :
		gm_(nullptr), //
		leftPaddle_(nullptr), //
		rightPaddle_(nullptr), //
		ball_(nullptr) {
}

Game::~Game() {
	// delete all game objects
	for (GameObject *o : objs_) {
		delete o;
	}
}

void Game::init() {

	// initialize the SDL singleton
	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	// the ball
	ball_ = new Container();
	ball_->addComponent(new SimpleMove());
	ball_->addComponent(new BounceOnBorder());
//	ball_->addComponent(new RectangleRenderer(build_sdlcolor(0xff0000ff)));
	ball_->addComponent(
			new ImageRenderer(&sdlutils().images().at("tennis_ball")));

	ball_->setWidth(10.0f);
	ball_->setHeight(10.0f);
	ball_->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);



	// the left paddle
	leftPaddle_ = new Container();
	leftPaddle_->setWidth(10.0f);
	leftPaddle_->setHeight(50.0f);
	leftPaddle_->getPos().set(10, sdlutils().height() / 2 - 25);

//	auto leftPaddle_ic = new MovePaddleWithKeyBoard();
//	leftPaddle_ic->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A);
//	leftPaddle_->addComponent(leftPaddle_ic);
	leftPaddle_->addComponent(new AIPaddle(ball_));

	leftPaddle_->addComponent(
			new RectangleRenderer(build_sdlcolor(0xff0000ff)));
	leftPaddle_->addComponent(new SimpleMove());
	leftPaddle_->addComponent(new StopOnBorder());

	// the right paddle
	rightPaddle_ = new Container();
	rightPaddle_->setWidth(10.0f);
	rightPaddle_->setHeight(50.0f);
	rightPaddle_->getPos().set(sdlutils().width() - 15,
			sdlutils().height() / 2 - 25);

//	rightPaddle_->addComponent(new MovePaddleWithMouse());
	rightPaddle_->addComponent(new AIPaddle(ball_));

	rightPaddle_->addComponent(
			new EmptyRectangleRenderer(build_sdlcolor(0x00ff00ff)));

	rightPaddle_->addComponent(new SimpleMove());
	rightPaddle_->addComponent(new StopOnBorder());

	// game manager
	gm_ = new GameManager(ball_);
	gm_->addComponent(new GameCtrl());
	gm_->addComponent(new ScoreRenderer());
	gm_->addComponent(new InfoMsgs());

	// add them all to the list of game objects
	objs_.push_back(ball_);
	objs_.push_back(leftPaddle_);
	objs_.push_back(rightPaddle_);
	objs_.push_back(gm_);

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

		for (auto &o : objs_) {
			o->handleInput();
		}

		// update
		for (auto &o : objs_) {
			o->update();
		}

		checkCollisions();

		sdlutils().clearRenderer();

		// render
		for (auto &o : objs_) {
			o->render();
		}

		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

void Game::checkCollisions() {
	if (gm_->getState() != GameManager::RUNNING)
		return;

	// check if ball hits paddles
	if (Collisions::collides(leftPaddle_->getPos(), leftPaddle_->getWidth(),
			leftPaddle_->getHeight(), ball_->getPos(), ball_->getWidth(),
			ball_->getHeight())
			|| Collisions::collides(rightPaddle_->getPos(),
					rightPaddle_->getWidth(), rightPaddle_->getHeight(),
					ball_->getPos(), ball_->getWidth(), ball_->getHeight())) {

		// change the direction of the ball, and increment the speed
		auto &vel = ball_->getVel(); // the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (ball_->getPos().getX() < 0)
		gm_->onBallExit(GameManager::LEFT);
	else if (ball_->getPos().getX() + ball_->getWidth() > sdlutils().width())
		gm_->onBallExit(GameManager::RIGHT);
}

