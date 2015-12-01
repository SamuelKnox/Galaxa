
#define GAME_SPEED 10000

// ***** Backgrond Images *****
#define BG_WIDTH		640
#define BG_HEIGHT		960
#define NUM_BACKGROUNDS	2

// Title Screen
#define BG_TITLE_SCREEN		"assets/title_screen.png"
#define TITLE_NUM_SPRITES	1

// Space (in-game)
#define BG_SPACE			"assets/background2.png"
#define SPACE_NUM_SPRITES	2
#define SCROLL_RATE			0.10f

// ***** Sprite Images *****

// Player
#define PLAYER_SPRITE "assets/player.png"
#define PLAYER_SFX_FIRE	".\\assets\\sfx\\fire.mp3"
#define PLAYER_WIDTH		48
#define PLAYER_HEIGHT		48
#define PLAYER_NUM_SPRITES	1
#define MOVE_FORCE			3
#define SHOT_FORCE			5
#define SHOT_RATE			100
#define PLAYER_LIVES		3

// Enemies
#define ENEMY_SPRITE_GREEN	"assets/enemy_green.png"
#define ENEMY_SPRITE_PURPLE "assets/enemy_purple.png"
#define ENEMY_SFX_KILL	".\\assets\\sfx\\kill.mp3"
#define ENEMY_WIDTH					42
#define ENEMY_HEIGHT				38
#define ENEMY_NUM_SPRITES			1
#define ENEMY_MAX_ENEMIES			5
#define ENEMY_RESPAWN_TIME_MILLISEC 1000
#define ENEMY_SHOOT_TIME_MILLISEC 600

// Projectiles
#define MISSILE_SPRITE		"assets/missile.png"
#define MISSILE_WIDTH		12
#define MISSILE_HEIGHT		20
#define MISSILE_NUM_SPRITES 1
#define MAX_NUM_MISSILES	100

// Explosions
#define EXPLOSION_PLAYER_SPRITE "assets/explosion_player.png"
#define EXPLOSION_PLAYER_WIDTH			80
#define EXPLOSION_PLAYER_HEIGHT			72
#define EXPLOSION_ENEMY_SPRITE	"assets/explosion_enemy.png"
#define EXPLOSION_ENEMY_WIDTH			56
#define EXPLOSION_ENEMY_HEIGHT			56
#define EXPLOSION_NUM_SPRITES			4
#define MAX_EXPLOSIONS					ENEMY_MAX_ENEMIES+1
#define EXPLOSION_RATE_MS				100

// Scoring Points
#define POINTS_SPRITES		"assets/scores.png"
#define POINTS_WIDTH		36
#define POINTS_HEIGHT		16
#define POINTS_NUM_SPRITES	8
#define POINTS_RATE_MS		500

// Game Over
#define GAMEOVER_SPRITE		"assets/gameover.png"
#define GAMEOVER_WIDTH		360
#define GAMEOVER_HEIGHT		60

// Fields
#define NUM_HOLES	16
#define LINE_WIDTH	1

// FallTrajectory
#define FALL_TRAJECTORY_SPEED 100.0f
