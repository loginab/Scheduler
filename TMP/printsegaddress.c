
int printsegaddress()
{
	extern int edata;
	extern int etext;
	extern int end;


	printf("\n\n Task 2 (printsegaddress)");

		


//	printf("\n Current: etext[0x%08X]=0x%08X   data[0x%08X]=0x%08X",&etext,*(&etext),&edata,*(&edata));
	
//	printf("\n\nINT: etext =%d" ,*(&etext+2));
	



	printf("\n Current: etext[0x%08X]=0x%08X,data[0x%08X]=0x%08X",&etext,*(&etext),&edata,*(&edata));
	//printf(", data 0x%08X=",&edata);

	printf("\n Preceding: etext[0x%08X]=0x%08X,data[0x%08X]=0x%08X",&etext-1,*(&etext-1),&edata-1,*(&edata-1));
	//printf("\nPreceding: etext=0x%08X,data=0x%08X",&etext-1,&edata-1);


	printf("\n Following: etext[0x%08X]=0x%08X,data[0x%08X]=0x%08X",&etext+1,*(&etext+1),&edata+1,*(&edata+1));
	//printf("\nFollowing: etext=0x%08X,data=0x%08X",&etext+4,&edata+4);*/
	return 0;

}
