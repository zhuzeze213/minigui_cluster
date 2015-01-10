extern char *weather;
inline void get_weather()
{
	int temp;
	temp=rand()%4;
	switch(temp)
	{
		case 0:
		weather="sunny";break;
		case 1:
		weather="rainy";break;
		case 2:
		weather="cloudy";break;
		case 3:
		weather="windy";break;
		default:
		printf("no such weather\n");
	}
}
