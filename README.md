# averageteenagefollower
I have implemented this code in C
In the my implementation, I have created a Graph as an array of linked lists.
Each element of array represents a Veretx and linked list associated with it represents it's succesors.

e.g. for an input dataset like 
3 23 45 75 93
graph will be populated as follows: 
array[i].VeretxId = 3
[3] ->[93]->[75]->[45]->[23]
      <----Linked list ---->

