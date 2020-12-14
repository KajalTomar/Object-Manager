# Object-Manager

<p>I wrote get methods in ObjectManager.c to retrieve refCount and the current number
of objects to help me test the add/drop reference, destroyPool, and compact functions.
Then was I was able make sure my results were accurate.

I think we are not supposed to change the header file which is why I rewrote my main 
file without those functions. Now I can manually check the state of the pool to see 
if my functions work.

If I am mistaken and I should have kept the get functions please let me know and I can
submit that version.

Thank you!</p>
                                                                                                                                                                                                            ~                    
