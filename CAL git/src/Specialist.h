/*
 * Specialist.h
 *
 *  Created on: 26 de Abr de 2014
 *      Author: Anaís
 */

#ifndef SPECIALIST_H_
#define SPECIALIST_H_

#include <vector>
#include <string>

using namespace std;


class Specialist {

public:
	Specialist();
	Specialist(int id, string name);
	~Specialist();
	void addSkill(string skill);
	void setName(string n);
	void setSkills(vector<string> sk);
	void setComps(vector<int> c);
	vector<string> getSkills() const;
	string getName() const;
	int getID() const;
	vector<int> getComps() const;
	bool operator ==(const Specialist &s2) const;
	bool operator !=(const Specialist &s2) const;
	bool hasProjectSkills(vector<string> sk) const;
	Specialist getSpecialistByID(int id) const;

private:
	vector<string> skills;
	string name;
	vector <int> comps;
	int id;

};



#endif /* SPECIALIST_H_ */
