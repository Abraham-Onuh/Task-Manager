#pragma once

#include <iostream>
#include <fstream> 
#include <string>
#include <string.h> 
#include <conio.h> 
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>

using namespace std;

typedef struct {
	int day;
	int month;
	int year;
} Date;


class Task
{
protected:
	string name, info;      //name of the task and a short description of the task
	Date start, finish;    // time interval for completing a task
	char category;        //'A'-University, 'B' -Work, 'C' -Household
	char priority;       //'1', '2', '3'...  -in increasing order of priority
	Date present;          //for receiving "today's" date (the date a user uses the program)


public:
	Task();         //default constructor because of inheritance

	static int total;   //number of tasks on the text file.
	                    //This is incremented whenever there is a constructor call of the subclasses

	void begin();

	        //program functions
	void startmenu();
	void addtask();       //add a new task entry
	void searchtask();   //search and display tasks according to category and priority
	void showtasks();     //display all tasks entered
	void deletetask();    //delete a task (specify which task by giving task name) 


	           //getters
	string getname() const;
	string getinfo() const;
	Date getstart() const;
	Date getfinish() const;
	char getcategory() const;
	char getpriority() const;

	
	string getstatus(Date today) const;       //compares the date given (the current/present date)
	string namecategory(char categoryin) const;    //retruns the name of the task's category (Uni or Work or Household)
													//based on an entered character ('A', 'B', or 'C' respectively)

};

//int Task::total = 0;


class University : public Task
{

public:
	University(string name_in, string info_in, Date start_in, Date finish_in, char category_in, char priority_in)
	{
		this->name = name_in;
		this->info = info_in;
		this->start.day = start_in.day;
		this->start.month = start_in.month;
		this->start.year = start_in.year;
		this->finish.day = finish_in.day;
		this->finish.month = finish_in.month;
		this->finish.year = finish_in.year;
		this->category = category_in;
		this->priority = priority_in;
		total++;
	}

};



class Work : public Task
{
public:
	Work(string name_in, string info_in, Date start_in, Date finish_in, char category_in, char priority_in)
	{
		this->name = name_in;
		this->info = info_in;
		this->start.day = start_in.day;
		this->start.month = start_in.month;
		this->start.year = start_in.year;
		this->finish.day = finish_in.day;
		this->finish.month = finish_in.month;
		this->finish.year = finish_in.year;
		this->category = category_in;
		this->priority = priority_in;
		total++;
	}

};



class Household : public Task
{

public:
	Household(string name_in, string info_in, Date start_in, Date finish_in, char category_in, char priority_in)
	{
		this->name = name_in;
		this->info = info_in;
		this->start.day = start_in.day;
		this->start.month = start_in.month;
		this->start.year = start_in.year;
		this->finish.day = finish_in.day;
		this->finish.month = finish_in.month;
		this->finish.year = finish_in.year;
		this->category = category_in;
		this->priority = priority_in;
		total++;
	}

};