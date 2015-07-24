struct flightListNode
{
	PassengerTreeNodePtr rootPassengerTreeNodePtr;
	Flight data;
	struct flightListNode *nextFlightListNodePtr;
};