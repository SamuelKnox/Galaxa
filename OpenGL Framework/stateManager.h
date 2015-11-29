class StateManagerC
{
public:
	enum STATES
	{
		TITLE_SCREEN,
		FOREST,
		ARROW_PITS,
		FOUR_DIAMOND_PITS,
		WIDE_DIAMOND_PITS,
		EIGHT_PITS,
		WASHINGTON_DC,	
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