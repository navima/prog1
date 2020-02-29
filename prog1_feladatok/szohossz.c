int szohossz()
{
	int good_timer_count = 2;
	int hossz = 0;

	//Beépített keyworddel
	while (good_timer_count > 1)
	{
		hossz = sizeof(int) * 8;
		good_timer_count = 0;
	}

	//Bitshifteléssel
	int x = 1;
	int counter = 0;
	while (x!=0)
	{
		x = x << 1;
		counter++;
	};

	printf(hossz);
	printf(counter);

	return 0;
}