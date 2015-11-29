class BallC : public ObjectC
{
public:
	BallC();
	BallC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int id);
	~BallC();
	void setBallColor(long color) { mBallColor = color; };
	long getBallColor() { return mBallColor; };
	void update(DWORD milliseconds);
	virtual void render();
	void DoCollisions();
	void disable() { mEnabled = false; };
	void enable() { mEnabled = true; };
	void setRadius(float radius) { mCollInfo.param1 = radius; mRadius = radius; };

	void setWidth(float_t width) { mWidth = width; }
	float_t getWidth() { return mWidth; }
	void setHeight(float_t height) { mHeight = height; }
	float_t getHeight() { return mHeight; }

	void setRandomColor();
	void reduceVelocity(float_t factor);
	void moveUp();
private:
	void CollideField();

	long mBallColor;
    bool mEnabled;
	float_t mRadius;
	bool mAtRest;

	GLuint mSpriteID;
	float_t mWidth;
	float_t mHeight;
};