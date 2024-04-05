#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <map>

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

    Scheduler(Family fam, TV_Channel channel)
    {
        for (int i = 0; i < 24; i++)
        {
            vector<Member> free;

            for (auto &it_member : fam.family_members)
            {
                for (auto it_available : it_member.availabilty)
                {
                    if (it_available.start_time == i)
                    {
                        free.push_back(it_member);
                    }
                }
            }

            if (free.size() == 0)
            {
                continue;
            }
            else if (free.size() == 1)
            {
                for (auto &it : channel.show_list)
                {
                    if ((it.member_list.size() == 1) && (it.member_list.front() == free[0].name))
                    {
                        pair<string, string> data = make_pair(free[0].name, it.name);
                        Schedule.insert({i, data});
                        it.member_list.pop_front();
                        free[0].p_copy++;
                        break;
                    }
                }
            }
            /*else if(free.size()>1){
                for(int i=0; i<free.size(); i++)
                {
                    int count = 0;
                    string common;

                    for(auto it : channel.show_list)
                    {
                        for(auto it2 = it.member_list.begin(); it2!=it.member_list.end(); ++it1)
                        {
                            if(it2==free[i].name || it1==free)
                        }
                    }
                }*/
        }
    }
};

int main()
{

    Family American("Members.txt");

    cout << American.family_members[1].availabilty[0].start_time << endl;

    TV_Channel Sony;
    Sony.setdata("Shows.txt", American);

    cout << Sony.show_list[0].name << endl;

    for (auto it = Sony.show_list[0].member_list.begin(); it != Sony.show_list[0].member_list.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    Scheduler schedule(American, Sony);

    for (auto it : schedule.Schedule)
    {
        cout<<it.first<<" "<<it.second.first<<" "<<it.second.second<< endl;
    }
    /*Sony.show_list[1].member_list.pop_front();
    cout<<Sony.show_list[1].member_list.front();
    */
    return 0;
}
