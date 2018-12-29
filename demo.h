struct node
{
	char no[20];
	char name[20];
	struct node *next;
};


struct date
{
	int year;
	int month;
	int day;
};


struct stu_info
{
	char no[12];
	char name[20];
	char gender;
	struct date birthday;
};

