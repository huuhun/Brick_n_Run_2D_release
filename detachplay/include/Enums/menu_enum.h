#pragma once
enum DeadDecision{
	NOTHING = 0,
	PLAY_TRY_AGAIN = 1,
	BACK_TO_MENU = 2
};

enum IntroDecision : int {
	INTRO_NOTHING = 3,
	PLAY = 4,
	CHOOSE_TUTORIAL = 5,
	EXIT = 6,
};

enum MenuState : int {
	INTRO_MENU = 7,
	DEAD_MENU = 8,
	PLAYING = 9,
	NONE_STATE = 10,
	PAUSED = 11,
	TUTORIAL=13,
};

enum PauseDecision : int {
	PAUSE_GAME = 12,
};