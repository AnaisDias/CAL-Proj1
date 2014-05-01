/*
 * Specialist.cpp
 *
 *  Created on: 26 de Abr de 2014
 *      Author: Anaís
 */

#include "Specialist.h"


Specialist::Specialist()
{
	id=0;
}

Specialist::~Specialist(){

}

Specialist::Specialist(int id, string name)
{
	this->id=id;
	this->name=name;
}

void Specialist::addSkill(string skill)
{
	skills.push_back(skill);
}

void Specialist::setName(string name)
{
	this->name=name;
}

void Specialist::setSkills(vector<string> sk)
{
	this->skills=sk;
}

void Specialist::setComps(vector<int> c)
{
	this->comps=c;
}

vector<string> Specialist::getSkills() const
{
	return this->skills;
}

string Specialist::getName() const{
	return this->name;
}

int Specialist::getID() const {
	return id;
}
vector<int> Specialist::getComps() const {
	return comps;
}

bool Specialist::operator ==(const Specialist &s2) const{
	return (id == s2.getID());
}

bool Specialist::operator !=(const Specialist &s2) const{
	return !(*this == s2);
}

//returns true if specialist has at least one of the required skills
bool Specialist::hasProjectSkills(vector<string> sk) const {

	bool done = false;


	for(int i=0; i<skills.size(); i++)
	{
		if(!done)
		{
			for(int j=0; j<sk.size(); j++)
			{
				if(!done)
				{
					if (skills[i] == sk[j]) {
						done=true;
						return done;
					}
				}
				else if (done) break;
			}
		}
		else if (done) break;
	}




	if (!done)
		return false;

	return false;
}

