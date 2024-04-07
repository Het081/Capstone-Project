CAPSTONE PROJECT B. TECH ICT 2023
 
PROBLEM:  TV CHANNEL SCHEDULER 


DONE BY: 
1) HET RANK: 202301081
2) KRISHNA KANODIA: 202301038
3) YUNUS KOTHARI: 202301045
4) AYUSH PATEL: 202301084



INSTRUCTOR: SOURISH DAS GUPTA





ALGORITHM: 

INPUT: Text files of Family members(N) and shows names(M)

Procedure: Create a class of Member consists of name, Favorite shows, availability shows as data member.

Create a class of Family in order to access data of each member. Class Availability Slots would have start time and end time as their members.

Create a hash map of fixed size i.e. consists of 24 key value pairs. Hash Map would have keys (0 - 23). It will store Name and favorite shows according to their Availability slots. 

For example, Member 1 has availability slot 8 - 9 and it would be mapped to key value = 8. According to that every member would be added to hash map as per their availability slots. It has minimal chance of collision in hash map.

Create a linked list for all shows. Initially all shows list would be pointing to NULL. Iterate through every member data and append their name in show lists according to their Favorite shows. This would result in creation of lists where members of same Favorite shows are listed in it. 

OUTPUT: Check for no of member in a time slot. If there is only one member in that slot, assign a show that is unique (which is favorite show of him/her) or else assign any favorite show of him/her. Increase value of p (min On Timeslots) and remove his time slot from that list.

If there are more than one member in a time slot check for any common favorite show of them if there assign to them and increment the value of p by 1 else it will be a conflict-of-interest check for their p value and assign a show who has lowest value of p.

At last return Notification to each member about their favorite show in that time interval and the scheduler minimize total episode misses and members will get time for p slots.





DATA STRUCTURES USED: 

Data Structures used are Hash Map and Link List.

 Hash map provides us the constant time average case performance for insertion searching and deletion operations. Making them very efficient for storing and retrieving key-value pairs.

It allows for a wide range of key types, including custom object, string, integers, etc.

Hash maps are relatively easy to use. The average time complexity of basic operations in hash maps are: 

1) Insertion (including inserting key value pairs): O (1) on average 

2) Searching: on average is O (1) depending on hash function used.

3) Deletion: O (1) on average.

Overall time complexity for hash maps is O (1) on average might vary depending on other conditions. Also, they are easy to implement and has less time complexity as compared to data structures.

Next data structure is used Link list. We used list to store the members who have same favorite shows. We used it instead of array as we do not know the number of members who has same favorite show so it would be costly in terms of space. The time complexity of link list for basic operation is 

Insertion at Beginning is O (1) as compared to array where array has O (1). But we need to shift all the elements to right if element is present at top in array. 

Deletion is O (1) in link list but in array we need to fetch the element by traversing that leads to O(n) 

Although searching has O(n) time complexity in both link list and array but link list has dynamic memory space allocation and does not require continuous memory space.

Overall, we felt hash maps and link list are much better data structure than other in terms of time and space complexity in order to solve the problem of TV Channel Scheduler.


		


CONTRIBUTION:

Everybody in the group contributed equally in the project. Everybody had an active participation in the meetings. Everybody came up with the best possible ideas they could give.

Het: Wrote the algorithm and also updated the Hash Function in the final code. Was responsible of all the hash part of the code.

Krishna: Contributed in the documentation part of the project and also contributed in the algorithm of the code. Also wrote the main function of the code.

Yunus: Contributed in the algorithm part of the project and also updated and created the function where there are more than 1 member free.

Aayush: Contributed in writing all the part of the code where the data was to be taken as the input from Member and Shows file.






Example of the Solution:

INPUT:
Members File:
Jack 7 Narcos Lucifer Breaking_Bad Game_of_thrones Teen_wolf Legacies Stranger_things 8 9 12 13 16 17 20 21 22 23 
BOB 5 Game_of_thrones House_of_the_dragon Teen_wolf Legacies Breaking_Bad 4 5 8 9 10 11 16 17 18 19 20 21
Tessa 3 Lucifer Narcos Lost_in_space 6 7 12 13 15 16 23 24
Jessica 5 Riverdale vampire_diaries Breaking_Bad Lucifer Lost_in_space 7 8 11 12 15 16 17 18 19 20

    Shows File:
        Breaking_Bad
        Game_of_thrones
        Witcher
        House_of_the_dragon
        Narcos
        Stranger_things
        Lucifer
        Lost_in_space
        Riverdale
        vampire_diaries
        Legacies
        Teen_wolf

OUTPUT:

The Time is: 4:00
BOB watch the show House_of_the_dragon in your free time

************************************************

The Time is: 6:00
Tessa watch the show Lost_in_space in your free time

************************************************

The Time is: 7:00
Jessica watch the show Lost_in_space in your free time

************************************************

The Time is: 8:00
Jack watch the show Breaking_Bad in your free time

************************************************

The Time is: 8:00
BOB watch the show Breaking_Bad in your free time

************************************************

The Time is: 10:00
BOB watch the show Teen_wolf in your free time

************************************************

The Time is: 11:00
Jessica watch the show Breaking_Bad in your free time

************************************************

The Time is: 12:00
Jack watch the show Narcos in your free time

************************************************

The Time is: 12:00
Tessa watch the show Narcos in your free time

************************************************

The Time is: 15:00
Tessa watch the show Lucifer in your free time

************************************************

The Time is: 15:00
Jessica watch the show Lucifer in your free time

************************************************

The Time is: 16:00
Jack watch the show Game_of_thrones in your free time

************************************************

The Time is: 16:00
BOB watch the show Game_of_thrones in your free time

************************************************

The Time is: 17:00
Jessica watch the show Riverdale in your free time

************************************************

The Time is: 18:00
BOB watch the show Legacies in your free time

************************************************

The Time is: 19:00
Jessica watch the show vampire_diaries in your free time

************************************************

The Time is: 20:00
Jack watch the show Stranger_things in your free time

************************************************

The Time is: 22:00
Jack watch the show Lucifer in your free time

************************************************

Every member watched atleast 3 shows today

