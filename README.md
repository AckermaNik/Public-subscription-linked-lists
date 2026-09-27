# Public Subscription System

This C project implements a small Public Subscription System (PSS). Information items belong to one or more of 64 groups, and subscribers register for selected groups. A subscriber can consume the information available in their subscribed groups, be removed from the system, or have the data structures printed for inspection.

## How it works

The implementation combines a fixed-size group table with three linked-list relationships and per-subscriber cursors:

- **Group table:** `G` is a global array of 64 `Group` structures, indexed directly by group ID (`0–63`). Each `Group` stores its ID, the head and tail of its information list, and the head of its subscriber list. This avoids searching for a group by ID.
- **Per-group information list:** each `Group` owns a doubly linked list of `Info` nodes. A node stores the information ID and timestamp, `iprev`/`inext` links, and a 64-entry `igp` membership array indicating which groups the information belongs to. The list is maintained in timestamp order, and the head/tail pointers support insertion at either end as well as between nodes.
- **Per-group subscriber list:** each group also has a singly linked list of `Subscription` nodes. Each node stores a subscriber ID, providing a group-oriented view of who is subscribed to that group.
- **Global subscriber list:** `subinfohead` points to a singly linked list of `SubInfo` records. A record stores the subscriber ID and registration timestamp, plus `sgp[64]`, an array of pointers into group information lists. For a subscribed group, the pointer acts as that subscriber's position in the group's information history; a sentinel pointer marks groups to which the subscriber is not subscribed. This is the subscriber-oriented view, complementing the per-group subscription lists.

The two subscription indexes serve different lookups: a group's `Subscription` list makes it possible to enumerate that group's subscribers, while `SubInfo.sgp` lets a subscriber track progress across each selected group's information. On `Consume`, the program displays the information for the subscriber's selected groups and advances each applicable cursor to the most recent node, so subsequent consumption begins from that position.

Information and subscriber records are inserted in timestamp order. `Delete_Subscriber` removes the subscriber from the global list and from each group's subscriber list. `free_all` releases the allocated list nodes when processing is complete.

The program reads one event per line from a text file:

```text
I <timestamp> <info_id> <group_id>... -1
S <timestamp> <subscriber_id> <group_id>... -1
C <subscriber_id>
D <subscriber_id>
P
```

`I` inserts information into the listed groups; `S` registers a subscriber for groups; `C` consumes group information; `D` deletes a subscriber; and `P` prints the system state. Lines beginning with `#` are treated as comments. Group IDs must be within `0–63`.

## Build and run

With GCC:

```sh
gcc -ansi main.c pss.c -o pss
./pss simple_insert.txt
```

Other included input scenarios are `mixed_inserts_delete_consume.txt`, `complex_inserts.txt`, `complex_delete_consume.txt`, and `big_test.txt`.

## Files

- `main.c` parses the event file and calls the PSS operations.
- `pss.c` defines the 64-group table and global subscriber-list head, and implements the linked-list operations, event handlers, printing, and cleanup.
- `pss.h` declares `Info`, `Subscription`, `Group`, and `SubInfo`, along with the shared constants and public function prototypes.
- The `.txt` files provide sample event sequences for exercising the program.
- `.project`, `.cproject`, and `.settings/` are Eclipse CDT project configuration files.

This is an educational implementation; the sample executable `main.exe` is a prebuilt artifact and may not match the current source or run on every platform.
