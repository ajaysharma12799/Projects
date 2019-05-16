#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

//creating structure for student;
typedef struct
{
	int school_id;
	char name[20];
	int roll;
}student;

//function to Add New Student
void Add_Record()
{
	student st;
	FILE *f;
	printf("Enter Student School ID : ");
	scanf("%d",&st.school_id);
	printf("Enter Student Name :");
	flushall();
	gets(st.name);
	printf("Enter Student Roll Number :");
	scanf("%d",&st.roll);

	//creating file in append mode
	f = fopen("info.dat","a");
	//checking condition for file pointer
	if(f == NULL)
	{
		printf("Fail To Create File\n");
	}
	else
	{
		//writing data into file using fwrite() which is structurewise file writing function
		fwrite(&st,sizeof(st),1,f);
	}
	printf("One Record Added\n");
	fclose(f);
}

//function to Modify Existing Student Info
void Modify_Record()
{
	FILE *f;
	student st;
	int serial_number=0,change;
	long location;
	//opening file for reading and writing mode
	f = fopen("info.dat","r+");

	//checking condition for NULL Pointer
	if(f == NULL)
	{
		printf("Fail To Open File\n");
	}
	else
	{
		printf("Serial Number       School_ID      Name           Roll Number\n");
		while(fread(&st,sizeof(st),1,f))
		{
			serial_number++;
			printf("%d %20d %16s %15d\n",serial_number,st.school_id,st.name,st.roll);
		}
		printf("\n\nEnter Index Value which you want to Change :");
		scanf("%d",&serial_number);

		//taking input for the New Value
		printf("\n\nEnter New School_ID :");
		scanf("%d",&st.school_id);
		printf("\n\nEnter New Student Name :");
		flushall();
		gets(st.name);
		printf("\n\nEnter New Roll Number :");
		scanf("%d",&st.roll);

		//getting location of index value
		location = (serial_number-1)*sizeof(st);
		fseek(f,location,SEEK_SET);
		change = fwrite((&st),sizeof(st),1,f);

		//checking condition whether it is modified or not
		if(change == 0)
		{
			printf("\n\nFail To Modify.");
		}
		else
		{
			printf("\n\nSuccessfully Modified.");
		}
	}
	fclose(f);
}

//function to Delete existing record
void Delete_Record()
{
	printf("Function to delete existing record.\n");
}

//function to Display Student Info
void Display_Record()
{
	FILE *f;
	student st;

	//opening file in read mode
	f = fopen("info.dat","r");
	//checking the condition
	if(f == NULL)
	{
		printf("Fail To Open File.\n");
	}
	else
	{
		printf("School_ID      Name           Roll Number\n");
		while(fread(&st,sizeof(st),1,f))
		{
			printf("%5d %14s %15d\n",st.school_id,st.name,st.roll);
		}
	}
}

//function to calculate size of file
void Calculate_Size()
{
	FILE *f;
	long location1,location2;//used for getting size of file

	//opening file in reading mode
	f = fopen("info.dat","r");

	//checking condition
	if(f == NULL)
	{
		printf("Fail To open File.\n");
	}
	else
	{
		//getting size of starting point of file
		fseek(f,0,SEEK_SET);
		location1 = ftell(f);

		//getting size of ending point of file
		fseek(f,0,SEEK_END);
		location2 = ftell(f);

		printf("Size of File :%d bytes.\n",location2 - location1);
	}
	fclose(f);
}

//Main Function Starts
int main(int argc, char *argv)
{
	int ans;
	clrscr();
	do
	{
		printf("1. To Add New Student....\n");
		printf("2. To Modify Existing Student....\n");
		printf("3. To Delete Existing Record From File....\n");
		printf("4. To Display All Student Info....\n");
		printf("5. To Calculate Size of File....\n");
		printf("0. Exit Application....\n");
		printf("Enter Choice From Above Menu :");
		scanf("%d",&ans);
		switch(ans)
		{
			case 1:
				Add_Record();
				break;
			case 2:
				Modify_Record();
				break;
			case 3:
				Delete_Record();
				break;
			case 4:
				Display_Record();
				break;
			case 5:
				Calculate_Size();
				break;
		}
	}while(ans != 0);
	getch();
	return 0;
}