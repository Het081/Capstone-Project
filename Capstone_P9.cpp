#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <map>

#define p 3 //this is the number of time slots every member wants to get on time

using namespace std;

class Availability_Slots
{
public:
    int start_time;
    int end_time;
};

class Member
{
public:
    string name;
    vector<string> favorite_shows;
    vector<Availability_Slots> availabilty;
    int p_copy;
};

class Family
{
public:
    int number_of_members;
    vector<Member> family_members;

    Family(string datafile)
    {
        ifstream data(datafile);
        string temp;

        while (getline(data, temp))
        {

            istringstream iss(temp);
            string name;
            iss >> name;
            Member m;
            m.name = name;

            string series;
            int no_of_fav_series;
            iss >> no_of_fav_series;

            while (no_of_fav_series > 0 && iss >> series)
            {
                m.favorite_shows.push_back(series);
                no_of_fav_series--;
            }

            Availability_Slots slots;

            while (iss >> slots.start_time >> slots.end_time)
            {
                m.availabilty.push_back(slots);
            }
            m.p_copy = 0;
            family_members.push_back(m);
            number_of_members++;
        }
        data.close();
    }
};

class Show
{
public:
    list<string> member_list;
    string name;
};

class TV_Channel
{
public:
    vector<Show> show_list;

    void setdata(string datafile, Family fam)
    {

        ifstream data(datafile);
        string temp;

        while (getline(data, temp))
        {
            Show s;
            s.name = temp;

            for (auto it : fam.family_members)
            {
                for (auto it1 : it.favorite_shows)
                {
                    if (s.name == it1)
                    {
                        s.member_list.push_back(it.name);
                    }
                }
            }

            show_list.push_back(s);
        }

        data.close();
    }
};

class Scheduler
{
public:
    multimap<int, pair<string, string>> Schedule;

    Scheduler(Family &fam, TV_Channel &channel)
    {
        for (int i = 0; i < 24; i++)
        {
            vector<Member *> free;
            vector<string> fav_shows;

            for (auto &it_member : fam.family_members)
            {
                for (auto it_available : it_member.availabilty)
                {
                    if (it_available.start_time == i)
                    {
                        free.push_back(&it_member);
                    }
                }
            }

            if (free.size() == 0)
            {
                continue;
            }
            else if (free.size() == 1)
            {
                bool inserted = false;
                for (auto &it : channel.show_list)
                {
                    if ((it.member_list.size() == 1) && (it.member_list.front() == free[0]->name))
                    {
                        pair<string, string> data = make_pair(free[0]->name, it.name);
                        Schedule.insert({i, data});
                        it.member_list.remove(free[0]->name);
                        free[0]->p_copy++;
                        inserted=true;
                        break;
                    }
                }

                if(!inserted)
                {
                    string fav_s;

                    for(auto &fav : channel.show_list)
                    {
                        for(auto &member : fav.member_list)
                        {
                            if(member==free[0]->name)
                            {
                                fav_s = fav.name;
                            }
                        }
                    }

                    pair<string, string> data = make_pair(free[0]->name, fav_s);
                    Schedule.insert({i, data});
                    free[0]->p_copy++;
                    for(auto &it : channel.show_list)
                    {
                        if(it.name==fav_s)
                        {
                            it.member_list.remove(free[0]->name);
                            break;
                        }
                    }
                }

            }
            else if (free.size() > 1)
            {
                int count = 0;

                for (auto &it : channel.show_list)
                {
                     count = 0;

                    for (auto &it2 : it.member_list)
                    {
                        for (auto check : free)
                        {
                            if (it2 == check->name)
                            {
                                count++;
                                break;
                            }
                        }
                        if (count == free.size())
                        {
                            for (auto insert : free)
                            {
                                pair<string, string> data = make_pair(insert->name, it.name);
                                Schedule.insert({i, data});
                                insert->p_copy++;
                                it.member_list.remove(insert->name);
                            }
                            break;
                        }
                    }
                    if (count == free.size())
                    {
                        break;
                    }
                }
                if(count!=free.size()){
                Member *temp = free[0];
                for (auto &it2 : free)
                {
                    if (temp->p_copy >= it2->p_copy)
                    {
                        temp = it2;
                    }
                }

                for (auto &it : channel.show_list)
                {
                    int j = 0;

                    for (auto &it3 : it.member_list)
                    {
                        if ((it3 == temp->name))
                        {
                            pair<string, string> data = make_pair(temp->name, it.name);
                            Schedule.insert({i, data});
                            temp->p_copy++;
                            it.member_list.remove(it3);
                            j = 1;
                            break;
                        }
                    }
                    if (j == 1)
                    {
                        break;
                    }
                }
                }
            }
        }
    }

    void notify(Family fam)
    {
        for(auto it = Schedule.begin(); it!=Schedule.end(); it++)
        {
            if(it->second.second == "\0"){
                break;
            }

            cout<<"The Time is: "<<it->first<<":00"<<endl;
            cout<<it->second.first<<" watch the show "<<it->second.second<<" in your free time"<<endl<<endl;
            cout<<"************************************************"<<endl<<endl;
        }

        int check = 0;

        for(auto it : fam.family_members)
        {
            if(it.p_copy>p)
            {
                check++;
                continue;
            }
            else{
                cout<<"Every member did not watch "<<p<<" shows today"<<endl;
                break;
            }
        }

        if (check==fam.family_members.size())
        {
            cout<<"Every member watched atleast "<<p<<" shows today"<<endl;
        }
    }
};

int main()
{

    Family American("Members.txt");

    TV_Channel Sony;
    Sony.setdata("Shows.txt", American);

    Scheduler schedule(American, Sony);
    schedule.notify(American);

    return 0;
}
