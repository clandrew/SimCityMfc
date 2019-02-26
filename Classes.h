/*This is a class for creating a gridspace on the map. The map will consist of a 100x100
array of objects of this class.
*/
class CGridspace {
public:
	int pollution; 
	int landvalue; //Scaled from 1-100...
	int resproxim;
	int image; //What image the gridspace has. Used for landscaping (i.e. park, water, etc)
	int bcenter; //If there's no building center on the square, this is 0. If there is one,
	//thsi variable is assigned to a number (>0) to be associated with whatever building 
	//is there.
	bool road; //Whether there's a road on the space.
	bool rail; //Whether there's a railroad.
	bool pline; //Whether there's a powerline.
	bool power; //Whether the gridspace has power. (only really applicable for powerlines 
	//and buildings)
	bool builpart;//Whether this gridspace is part of a building.
	bool left;//Whether this gridspace is connected to a road/rail to the left
	bool right;//Same, but to the right
	bool up;//Same, but up
	bool down;//Same, but down
	bool pLeft;//Whether this gridspace is connected to a powerline on the left
	bool pRight;//Same, but right
	bool pUp;//Same, but up
	bool pDown;//Same, but down
	//It's worth noting that power lines need to use their own directional variables.
	//This is because powerlines actually can be built to overlap roads and 
	//rails.
	bool checked;//Whether this gridspace has been checked for power (a kind of temporary
	//variable).
	CGridspace() {image=0;road=FALSE;rail=FALSE;pline=FALSE;builpart=FALSE;bcenter=0;left=FALSE;right=FALSE;up=FALSE;down=FALSE;power=FALSE;checked=FALSE;pLeft=FALSE;pRight=FALSE;pUp=FALSE;pDown=FALSE;}
	//Everything has to initialized to be zero/false..
	~CGridspace() {;}
};