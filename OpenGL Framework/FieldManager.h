#include "gamedefs.h"
class FieldManagerC
{
public:
	static FieldManagerC	*CreateInstance();
	static FieldManagerC	*GetInstance() {return sInstance;};
	~FieldManagerC(){};

	FieldC* getFieldPtr();
	void init();
	void renderField();
	void shutdown();

	FieldC *border;
	/*FieldC *holes[NUM_HOLES];*/
private:
	static FieldManagerC *sInstance;
	FieldManagerC(){};
};