
#define GAME_SPEED 10000

// ***** Backgrond Images *****
#define BG_WIDTH		640
#define BG_HEIGHT		960
#define NUM_BACKGROUNDS	2
#define LINE_WIDTH	1

// Title Screen
#define BG_TITLE_SCREEN		"assets/title_screen.png"
#define TITLE_NUM_SPRITES	1

// Space (in-game)
#define BG_SPACE			"assets/background2.png"
#define START_SFX			".\\assets\\sfx\\start.mp3"
#define SPACE_NUM_SPRITES	2
#define SCROLL_RATE			0.10f

// ***** Sprite Images *****

// Player
#define PLAYER_SPRITE	"assets/player.png"
#define PLAYER_SFX_FIRE	".\\assets\\sfx\\fire.mp3"
#define PLAYER_SFX_HIT	".\\assets\\sfx\\hit.wav"
#define PLAYER_WIDTH		48
#define PLAYER_HEIGHT		48
#define PLAYER_NUM_SPRITES	1
#define MOVE_FORCE			3
#define PLAYER_LIVES		10

// Weapons
#define SHOT_FORCE			6
#define QUICK_SHOT_FORCE	9
#define SPREAD_SHOT_FORCE	4
#define SPREAD_SHOT_ANGLE	20
#define HOMING_ABILITY		0.1f
#define HOMING_FORCE		2
#define NORMAL_SHOT_RATE	100
#define QUICK_SHOT_RATE		50
#define SPREAD_SHOT_RATE	200
#define HOMING_SHOT_RATE	150
#define FAST_SHOT_WEAPON	"assets/sprites/weapons/fast_weapon.png"
#define SPREAD_SHOT_WEAPON	"assets/sprites/weapons/spread_weapon.png"
#define HOMING_SHOT_WEAPON	"assets/sprites/weapons/homing_weapon.png"
#define WEAPON_DROP_WIDTH		16
#define WEAPON_DROP_HEIGHT		64
#define WEAPON_DROP_NUM_SPRITES 1
#define MAX_WEAPON_DROPS		5
#define WEAPON_DROP_SPEED		0.5f

// Enemies
#define ENEMY_SPRITE_GREEN	"assets/enemy_green.png"
#define ENEMY_SPRITE_PURPLE "assets/enemy_purple.png"
#define ENEMY_SPRITE_RED	"assets/enemy_red.png"
#define ENEMY_SPRITE_YELLOW "assets/enemy_yellow.png"
#define ENEMY_SPRITE_SHIP	"assets/enemy_ship.png"
#define ENEMY_SFX_KILL		".\\assets\\sfx\\kill.mp3"
#define ENEMY_WIDTH					42
#define ENEMY_HEIGHT				38
#define ENEMY_NUM_SPRITES			1
#define ENEMY_BASE_HP				1
#define ENEMY_SHIP_HP				5

#define ENEMY_MAX_ENEMIES			30
#define ENEMY_RESPAWN_TIME_MILLISEC 1000
#define ENEMY_SHOOT_TIME_MILLISEC	600
#define BASE_ENEMIES_PER_WAVE		5

// FallTrajectory
#define FALL_TRAJECTORY_SPEED 100.0f

// SideTrajectory
#define SIDE_TRAJECTORY_SPEED 100.0f

// Projectiles
#define MISSILE_SPRITE		"assets/missile.png"
#define MISSILE_WIDTH		12
#define MISSILE_HEIGHT		20
#define MISSILE_NUM_SPRITES 1
#define MAX_NUM_MISSILES	1000

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

// Labels
#define GAMEOVER_SPRITE		"assets/gameover.png"
#define GAMEOVER_WIDTH		360
#define GAMEOVER_HEIGHT		60
#define HIGH_SCORE_SPRITE	"assets/label.png"
#define HIGH_SCORE_WIDTH	236
#define HIGH_SCORE_HEIGHT	16
#define HIGH_SCORE_X		-HIGH_SCORE_WIDTH / 2.0f
#define HIGH_SCORE_Y		(BG_HEIGHT / 2.0f) - HIGH_SCORE_HEIGHT
#define NUMBER_SPRITES		"assets/numbers.png"
#define NUMBER_WIDTH		16
#define NUMBER_HEIGHT		16
#define NUMBER_NUM_SPRITES	10

// Scoreboard
#define HORIZONTAL_LINE "assets/sprites/lines/horizontal_line.png"
#define VERTICAL_LINE	"assets/sprites/lines/vertical_line.png"
#define DIGIT_SEPARATION 24
#define SCOREBOARD_HORIZONTAL_WIDTH 16
#define SCOREBOARD_HORIZONTAL_HEIGHT 4
#define SCOREBOARD_VERTICAL_WIDTH 4
#define SCOREBOARD_VERTICAL_HEIGHT 16
#define NUM_LINES 63
#define SCOREBOARD_X	(BG_WIDTH / 3.0f)
#define SCOREBOARD_Y	(BG_HEIGHT / 2.0f) - SCOREBOARD_VERTICAL_HEIGHT / 2.0f

#define LEVEL_X				(BG_WIDTH / 2.0f) - NUMBER_WIDTH
#define LEVEL_Y				-(BG_HEIGHT / 2.0f) + NUMBER_HEIGHT
#define MAX_LEVEL_DIGITS	3