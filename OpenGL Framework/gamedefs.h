
// ***** Backgrond Images *****
#define BACKGROUND "assets/background.png"
#define BG_WIDTH		640
#define BG_HEIGHT		960
#define NUM_BACKGROUNDS 1

// ***** Sprite Images *****

// Player
#define PLAYER_SPRITE "assets/player.png"
#define PLAYER_WIDTH		48
#define PLAYER_HEIGHT		48
#define PLAYER_NUM_SPRITES	1
#define MOVE_FORCE			3
#define SHOT_FORCE			5
#define SHOT_RATE			100

// Enemies
#define ENEMY_SPRITE_GREEN	"assets/enemy_green.png"
#define ENEMY_SPRITE_PURPLE "assets/enemy_purple.png"
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
#define EXPLOSION_NUM_SPRITES			4
#define MAX_EXPLOSIONS					ENEMY_MAX_ENEMIES+1

// Fields
#define NUM_HOLES	16
#define LINE_WIDTH	1

// FallTrajectory
#define FALL_TRAJECTORY_SPEED 100.0f
