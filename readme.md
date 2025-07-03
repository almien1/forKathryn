# Welcome to the Formpipe C++ coding test

## Getting started

First: Please forgive us for the project names. Naming is one of the two hardest
problems in software development: naming, caching and off-by-one errors.

There are two projects: 

- FormPipeCodingTest - a console application for running and interfacing to the stuff
- SupportingProject - a dll, which should contain the actual stuff

You should be able to run the application and output a string.

You are free to implement the various asssignments as you see fit, but please jot down
some notes on your thought process along the way. You are of course allowed to use the
internet, search engines, AI-engines, whatever. Just make a note of it so we can discuss
it afterwards. 

The first task - just to get you started and warmed up - is to call and output the result
from the `helloWorldMessage()` function in `hello-world.cpp`. Then you'll have the 
console application linked (pun intended) up with the dll.

## Now you're warmed up

We really don't expect this to take more than 2-3 hours. And should you reach a point
where you simply say: This is too darn much then stop. It is not about a perfect, finished
application. It is about the though process along the way.

The real task is to create a small event sourced system for managing a simple
bank account using a command-line interface. 

### Event sourcing, you say, wtf is that?

It is a very simple design pattern where you store the state changes
that occur throughout the system as immutable events. The current
state is obtained by replaying these events - in the correct order, of course.

The pattern we're looking for is something along these lines:

UI -> Handler -> Command -> Event

The UI will in our case be the command line.

The UI will call a handler (corresponding to an endpoint in a web application).

The handler takes care of any external communication, if needed, e.g. loading
events from the database.

It is then up the actual command to verify whether the state is fit for
executing said command and then producing an event (in rare cases more)
that describes the state changed. This makes commands very suitable
for unit testing.

The Commands can be implemented using e.g. the **Decider** pattern, which
basically is a function which takes the current state and the command and
produces events:

`decide(state, command) => events`

If you are in doubt feel welcome to use e.g. ChatGpt for describing
these patterns and in general how to do event sourcing in C++ - we should
use the tools available to us! And it is simpler than it may sound
if you haven't done event sourcing before.

We have - on purpose - left out a description on how to handle the state.
There are, naturally, multiple ways to do this, but you choose. And
remember to describe why you choose! 

### The application

Is it up to you how you organize the code around this. But you
probably should consider the executable the "UI" (cmd line).
If you feel like adding a unit-test project, feel free to do so. 

The command line interface can be very simple, too:

- O name : Create account with name (O = open)
- A name : Make name the account that following commands will work on (A = Activate)
- C : Close account (C = Close)
- D amount : Deposit an amount (D = Deposit)
- W amount : Withdraw an amount (W = Withdraw)
- B : Show current balance (B = balance)
- T : List transactions on account (T = Transactions)

We are thinking events like

- AccountOpened
- AccountClosed
- MoneyDeposited
- MoneyWithdrawn (for start, just assume that overdrawing is okay!)

The events will quite likely have a common `Event` ancestor.

Don't go overboard when implementing. A naive implementation is
perfectly fine. We are mostly interested in how
you approach the problem and figure out how to implement it. So make
notes! :)

It is perfectly fine with if you just keep events stored in  memory. 
Storing it on disk is also fine, but definitely not necessary.

An extra task, if you feel up for it is error handling: e.g.  what to do when withdrawing
an amount that is too big. This is, of course, an expected sitation, so
nothing *exceptional* about it. Also just a discussion on what to do is
perfectly fine.