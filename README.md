<h2>Building Your Own Computer </h2>
<p><strong>8.18</strong>(Machine-LanguageProgramming)Let’s create a computer we’ll call the Simpletron. As its name implies,it’s a simple machine, but, as we’ll soon see, it’s a powerful one as well. The Simpletron runs programs written in the only language it directlyunderstands, that is, Simpletron Machine Language, or SML for short. </p>
<p>The Simpletron contains an <em>accumulator</em> —a “special register” in which information is put before the Simpletron uses that information in calculations or examines it in various ways. All information in the Simpletron is handled in terms of words. A word is a signed four-digit decimal number, such as +3364, -1293, +0007, -0001,etc. The Simpletron is equipped with a 100-word memory, and these words are referenced by their location numbers 00, 01, …, 99. </p>
<p>Before running an SML program, we must <em>load</em>, or place, the program into memory. The first instruction (or statement) of every SML program is always placed in location 00. The simulator will start executing at this location.</p>
<p> Each instruction written in SML occupies one word of the Simpletron’s memory; thus, instructions are signed four-digit decimal numbers. Assume that the sign of an SML instruction is always plus, but the sign of a data word may be either plus or minus. Each location in the Simpletron’s memory may contain an instruction, a data value used by a program or an unused (and hence undefined) area of memory. The  first two digits of each SML instruction are the *operation code* that specifies the operation to be performed. SML operation codes are shown in Fig. 8.23. </p>
<p>The last two digits of an SML instruction are the <em>operand</em> — the address of the memory location containing the word to which the operation applies.</p>


![](https://lh3.googleusercontent.com/gftAZ0K1XdFp8w_PKOaez0wv887ry_bT6p8HqNfgYEqMfWOaHsJM6wKSxIU9i3Dj9U3xwUkzTSQs "image1")
	

<p>Now let’s consider two simple SML programs. The first (Fig.8.24) reads two numbers from the keyboard and computes and prints their sum.The instruction +1007 reads the first number from the keyboard and places it into location 07 (which has been initialized to zero). Instruction +1008 reads the next number into location 08. The <strong><em>load</em></strong> instruction, +2007,places (copies) the first number into the accumulator, and the <strong><em>add</em></strong> instruction, +3008, adds the second number to the number in
the accumulator. All SML arithmetic instructions leave their results in the accumulator. The <strong><em>store</em></strong> instruction, +2109,
places (copies) the result back into memory location 09.Then the <strong><em>write</em></strong> instruction, +1109, takes the number and prints it (as a signed four-digit decimal number). The <strong><em>halt</em></strong> instruction, +4300, terminates execution.</p>

![](https://lh3.googleusercontent.com/_AbGMIjaBE2kn66xU7dV8EnGhsDKHTJYPDrrqfM2p00qi86v-0hUUmowgd5Rz3U71ECA2vbGAYcv "image2")


<p>The SML program in Fig.8.25 reads two numbers from the keyboard, then determines and prints the larger value. Note the use of the instruction +4107 as a conditional transfer of control, much the same asC++’s if statement.</p>


![](https://lh3.googleusercontent.com/kqFEKtgumr1dpjY1HmzOXTeyPW84jJJKfF-P-ofx1ecv9fPzpnemfSw94EJsd_MzZEVDXC0YfUxt "image3")

<p>Now write SML programs to accomplish each of the following tasks: <br>
 1. Use a sentinel-controlled loop to read positive numbers and compute and print their sum. Terminate input when a negative number is entered. <br>
 2. Use a counter-controlled loop to read seven numbers, some positive and some negative, and compute and print their average. <br>
 3.Read a series of numbers, and determine and print the largest number. The first number read indicates how many numbers should be processed. </p>
 <p><strong>8.19</strong> (Computer Simulator) It may at first seem outrageous, but in this problem you are going to build your own computer. No, you won’t be soldering components together. Rather, you’ll use the powerful technique of software-based simulation to create a software model of the Simpletron. Your Simpletron simulator will turn the computer you are using into a Simpletron, and you actually will be able to run, test and debug the SML programs you wrote in Exercise8.18. </p>
 <p>When you run your Simpletron simulator, it should begin by printing </p>

![](https://lh3.googleusercontent.com/cP289GWPN_6EKQcMgkFmoY1-PXqxc48U-CnHeV5j4YIKh8zv4cMMkD0SDeo06isIARIAV8OZqM4G "image4")

<p>Your program should simulate the Simpletron’s memory with a single-subscripted, 100-element array memory. Now assume that the simulator is running, and let’s examine the dialog as we enter the program of the second example of Exercise 8.18: </p>

![](https://lh3.googleusercontent.com/4rmz4aFNO7SGow_qy6aUPQOn8BbiuZCi1bS5UisKTD_0vZlMVUh0gK53rgB50W4rnke39_1qctk8 "image5")

<p>The numbers to the right of each ? in the preceding dialog represent the SML program instructions input by the user.</p>
<p>The SML program has now been placed (or loaded) into array memory. Now the Simpletron executes your SML program. Execution begins with the instruction in location 00 and, like C++, continues sequentially, unless directed to some other part of the program by a transfer of control. </p>
<p>Use variable <em>accumulator</em> to represent the accumulator register. Use variable i*nstructionCounter* to keep track of the location in memory that contains the instruction being performed. Use variable <em>operationCode</em> to indicate the operation currently being performed ( i.e.,the left two digits of the instruction word). Use variable <em>operand</em> to indicatethe memory location on which the current instruction operates. Thus, operand is the rightmost two digits of the instruction currently being performed. Do not execute instructions directly from memory. Rather, transfer the next instruction to be performed from memory to a variable called <em>instructionRegister</em>. Then “pick off” the left two digits and place them in <em>operationCode</em>, and “pick off” the right two digits and place them in operand. When Simpletron begins execution, the special registers are all initialized to zero.</p>
<p>Now let’s “walk through” the execution of the first SML instruction, +1009 in memory location 00. This is called an instruction execution cycle.</p>
 <p>The <em>instructionCounter</em> tells us the location of the next instruction to be performed. We fetch the contents of that location from memory by using the C++ statement</p>
 <p><em>instructionRegister =memory[ instructionCounter] ;</em> </p>
 <p>The operation code and operand are extracted from the instruction register by the statements</p>
 <p><em>operationCode = instructionRegister / 100; <br>operand = instructionRegister % 100;</em> </p>
<p>Now, the Simpletron must determine that the operation code is actually a <em>read</em> (versus a <em>write</em>,a <em>load</em>,etc.). A switch differentiates among the 12 operations of SML. In the switch statement, the behavior of various SML instructions is simulated as shown in Fig. 8.26 (we leave the others to you).</p>


![](https://lh3.googleusercontent.com/gr_ANOO4ePD_Uc5P1U0_rc7KAXvZU_OVkmXQ1X59JZExHgy5onhOLlPPaRAtMwjmQZvV6VWxzouQ "image6")

<p>The halt instruction also causes the Simpletron to print the name and contents of each register, as well as the complete contents of memory. Such a printout is often called a register and memory dump. To help you program your dump function, a sample dump format is shown in Fig. 8.27. Note that a dump after executing a Simpletron program would show the actual values of instructions and data values at the moment execution terminated. To format numbers with their sign as shown in the dump, use stream manipulator <strong>showpos</strong>. To disable the display of the sign, use stream manipulator <strong>noshowpos</strong>. For numbers that have fewer than fourdigits, you can format numbers with leading zeros between the sign and the value by using the following statement before outputting the value: </p>


![](https://lh3.googleusercontent.com/X2U2p1fXtqHbgnlaYphxTxnRpsGpNZhmWGobQzSEB-zb_hSM5yYKCYoxsCpT_3f7F0R9Pk7wEInP "image7")

<p>Parameterized stream manipulator <strong>setfill</strong> (from header iomanip) specifies the fill character that will appear between the sign and the value when a number is displayed with a field width of five characters but does not have four digits. (One position in the field width is reserved for the sign.) Stream manipulator <strong>internal</strong> indicates that the fill characters should appear between the sign and the numeric value . </p>

<p>Let’s proceed with the execution of our program’s first instruction—+1009 in location 00. As we’ve indicated, the switch statement simulates this by performing the C++  statement
<br> <em>cin >> memory[ operand ];</em> </p>
<p>A question mark (?) should be displayed on the screen before the cin statement executes to prompt the user for input. The Simpletron waits for the user to type a value and press the Enter key. The value is then read into location 09. </p>
<p>At this point, simulation of the first instruction is complete. All that remains is to prepare the Simpletron to execute the next instruction. The instruction just performed was not a transfer of control, so we need merely increment the instruction counter register as follows: <br><em>++instructionCounter;</em> </p>
<p>This completes the simulated execution of the first instruction. The entire process ( i.e.,the instruction execution cycle) begins anew with the fetch of the next instruction to execute.</p>
<p>Now let’s consider how to simulate the branching instructions (i.e., the transfers of control). All we need to do is a djust the value in the instructionCounter appropriately. Therefore, the unconditional branch instruction (40) is simulated in the switch as <br><em>instructionCounter = operand;</em> </p>
<p>The conditional “branch if accumulator is zero” instruction is simulated as 
<br><em>if (accumulator == 0 )</em> <br><em>instructionCounter =operand;</em></p>
<p>At this point, you should implement your Simpletron simulator and run each of the SML programs you wrote in Exercise 8.18.The variables that represent the Simpletron simulator’s memory and registers should be defined in main and passed to other functions by value or by reference as appropriate. </p>
<p>Your simulator should check for various types of errors. During the program loading phase, for example, each number the user types into the Simpletron’s memory must be in the range -9999 to +9999. Your simulator should use a while loop to test that each number entered is in this range and, if not, keep prompting the user to reenter the number until the user enters a correct number.</p>
<p>During the execution phase, your simulator should check for various serious errors, such as attempts to divide by zero, attempts to execute invalid operation codes, accumulator overflows (i.e., arithmetic operations resulting in values larger than +9999 or smaller than -9999) and the like. Such serious errorsare called <strong>fatal errors</strong>. When a fatal error is detected, your simulator should print an error message such as </p>


![](https://lh3.googleusercontent.com/W5x8trobmN90GiOguJHhN6OsdJ8TXaggo2hRd7U8ow-NdBIRy9gU-3sjaPUOGI9mtCjiPl6Ujah0 "image7")


<p>and should print a full register and memory dump in the format we’ve discussed previously. This will help the user locate the error in the program.</p>
<p> <strong>8.20</strong> (Project: Modifications to the Simpletron Simulator) InExercise 8.19, you wrote a software simulation of a computer that executes programs written in Simpletron Machine Language (SML). In this exercise,we propose several modifications and enhancements to the Simpletron Simulator. Some of the following modifications and enhancements may be required to execute
the programs produced by the compiler.

 1. Extend the Simpletron Simulator’s memory to contain 1000 memory locations to enable the Simpletron to handle larger programs. 
 2. Allow the simulator to perform modulus calculations. This requires an additional Simpletron Machine Language instruction. 
 3.Allow the simulator to perform exponentiation calculations. This requires an additional Simpletron Machine Language instruction.
