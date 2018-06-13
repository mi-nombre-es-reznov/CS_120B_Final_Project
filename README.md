# CS_120B_Final_Project
This will be my CS_120B final project - The Beat Trainer

<h1>Description of Project</h1>

<p>This repository is going to be tracking my changes and additions throughout these next couple of weeks.
The goal this far, is to get familiar with how to use Github and teach myself how to make a project work on here, for possible future projects.</p>

<h2>Here is the official start of my project! This is what a beginning of something looks like. This is a moment in history, not really, in which we get
to see the start of a project versus the completed product that is typically mass produced, sold, and sitting in our households.</p>

<br><br><br>

<p><img alt="Breadboard" src="breadboard.jpg" title="Awesome! This is the start of somthing amazing!!!" /></p>

<br><br><br>

<h2>Beginning of LCD screen</h2>
<p>This is the layout for the beginning messages of my LCD display. This statically gives you a dynamic perspective of what the code will display on the screen.<br><br>
<img alt="Beginning LCD display" src="first_pt_LCD_screen.JPG" title="The 'Paint' made version of an LCD display, showcasing (as you go down) a dynamic version of the LCD screen display
at the beginning of the game, before 'START'." /></p>

<p>After 5 different attempts at creating a working Finite State Machine (FSM), this one seems to be the most promising. This is also the one that I will be pushing my test code for to
test if it works properly. If this test code works as intended, then I shall stick with this one and use it in the final project - as the intro screen before 'START'. <br><br>
<img alt="Intro LCD FSM" src ="LCD_intro_FSM.jpeg" title="This is the Finite State Machine (FSM) that will be used to construct the first seen intro screen on the LCD display" /></p>

<br><br>

<h3>Test of the intro screen</h3>
<hr />

<p>Here are a few of the results on screen after running the <em>Beginning_Messages.c</em> file.<br><br>This is the scrolling message that the player will see upon powering on the game!<br><br>
<img src="Welcome_to_the.JPG" alt="Display of first part of the intro message, 'Welcome_to_the'." title="Scrolling intro message on LCD screen"/></p>

<br>

<p>Here is the second message that appears after the first finishes its cycle.<br><br>This is the flashing message that states, "Beat Trainer!"<br><br>
<img src="Beat_Trainer.JPG" alt="Beat Trainer" title="Secondary intro message that flashes 'Beat Trainer'."/></p>

<p><strong>If you would like to see the video of the code in action, you can see it <a href="https://youtu.be/miQS9gsfXd8" title="Let's go see it!!!">NOW!</a></strong></p>

<br><br>

<h2>Joystick</h2>
<p>I conducted a test to get the joystick working in the four main directions: north (up), south (down), east (right) and west (left).<br><br>
<strong>The video showing some results from the test is found <a href="https://youtu.be/vbepWqkhsp4" title="An early model of the working joystick">HERE!</strong></a></p>

<p>The joystick looks like this: <br><br> <img src="joystick.JPG" alt="Joystick image not found"  title="This is what the joystick looks like, it's just like the joystick on your favorite gaming controller." /></p>

<p>If you want to see the code that made the joystick work as a test, also the same code that is running the video example above, you can find that in the <em>Joystick_test.c</em> file. This is also the first complexity that
I had completed.</p>

<h2>LCD Screen</h2>

<p>For the LCD screen, there is nothing special about it, it displays my messages and messages like expected, but the other complexity that I have regarding this is the 8 custom characters that I had created.</p>

<p>I used the LCD screen to not only hold my messages, but it also the main spot or holding a players score.</p>

<h3>The Start Screen</h3>

<p>This picture shows the Start menu screen, with two of the custom characters being implemented. <br><br> <img src="Press_Start.JPG" alt="Part 1 of Start Screen not found!" title="Here is the first of the two pictures,
from the Start Screen."/></p>

<p>This second of 2 pictures shows the second part of the Menu Screen that gives it the dynamic, waiting effect. <br><br> <img src="Press_Start_2.JPG" alt="Part 2 of Start Screen not found!" title="Here is the second of the 
two pictures, from the Start Screen."/></p><br>

<p>These two pictures, when put together, produce a "push-button" like effect, especially when in a loop.</p><br>

<h3>Custom Characters</h3>
 
<p>The picture shows the different custom characters that I have in the game. <br><br> <img src="custom_chars.JPG" alt="Custom characters not found!" title="This is an image showcasing all 8 custom characters that I created."/>

<h3>The Menu Screen</h3>

<p>The Menu screen state, found in <em>menu_options.c</em>, holds the different gameplay options. It has both the <em>"Training"</em> and <em>"Performance"</em> mode in it, although, the Performance mode currently isn't operable.
Below are the different Menu options one has to choose from.</p><br><br>

<h4>Training Mode</h4>

<p>Here is the Training option Menu Screen. This option does not have an ability to be selected, as the options for this can be selected by scrolling up (and down after you begin with the initial up).
<br><br></p>

<img src="Training.JPG" alt="Training picture not found!" title="A picture of the Training screen option, in the Menu state." />

<br><br>

<h4>Quarter Notes</h4>

<p>Here is the option for Quarter Notes. In this game, the player will only tap on the first lit LED, the other three are there to help the player with timing.</p><br><br>

<img src="Quarter_Notes.JPG" alt="Quarter Notes picture not found!" title="This is the option menu for the Quarter Notes"/>