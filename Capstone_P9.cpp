#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class Availability_Slots{
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

};

class Family{
    public:
    vector<Member> family_members;

    Family(string datafile){
        ifstream data(datafile);
        string temp;

        while(getline(data,temp)){
            
            istringstream iss(temp);
            string name;
            iss >> name;
            Member m;
            m.name = name;

            string series;
            int no_of_fav_series;
            iss >> no_of_fav_series;
            
            while (no_of_fav_series>0 && iss>>series)
            {
                m.favorite_shows.push_back(series);
                no_of_fav_series--;
            }

            Availability_Slots slots;

            while (iss >> slots.start_time >> slots.end_time)
            {
                m.availabilty.push_back(slots);
            }

            family_members.push_back(m);
        }
            data.close();
    }
};

class Show{
    public:
        list <string> member_list;
        string name;
};

class TV_Channel{
    public:
    vector<Show> show_list;

    void setdata(string datafile, Family fam){
        
        ifstream data(datafile);
        string temp;

        while (getline(data, temp))
        {
            Show s;
            s.name = temp;

            for ( auto it : fam.family_members)
            {
                for (auto it1 : it.favorite_shows)
                {
                    if(s.name == it1){
                        s.member_list.push_back(it.name);
                    }
                }
                
            }

            show_list.push_back(s);
        }
        
        data.close();
    }
};

int main(){

    Family American("Members.txt");
    
    cout << American.family_members[1].availabilty[0].start_time<<endl;

    TV_Channel Sony;
    Sony.setdata("Shows.txt", American);

    cout<<Sony.show_list[0].name<<endl;

    for(auto it = Sony.show_list[0].member_list.begin(); it!=Sony.show_list[0].member_list.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    return 0;
}
