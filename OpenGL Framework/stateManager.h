class StateManagerC
{
public:
	enum
	{
		FOUR_DIAMOND_PITS,
		FOREST,
		WIDE_DIAMOND_PITS,
		EIGHT_PITS,
		ARROW_PITS,
		WASH_DC,
		TITLE_SCREEN,
		PIT,
		ET_HOME
	};

	static StateManagerC	*CreateInstance();
	static StateManagerC	*GetInstance() {return sInstance;};
	~StateManagerC(){};
	
	int32_t		getState();
	void		setState(int32_t stateToSet);
	void		shutdown();
private:
	static StateManagerC *sInstance;
	StateManagerC(){};
	int32_t		mCurrentState;
};