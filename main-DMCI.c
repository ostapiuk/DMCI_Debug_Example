/*********************************************************************************************
 * StateChange Lab
 * Note - this is not the best way to implement a state machine.  The code was written this
 * way to purposely create a bug...
 *********************************************************************************************/

#include <xc.h>

#define DMCI_STEP_WIDTH 245     // Used for delay()
#define SUFFICIENT_TIME 60      // Used for delay()

/*********************************************************************************************
 <<<<<<< STATE Definitions (enum)
 *********************************************************************************************/
enum states {STATE_INITAL = 0,    // State 0 description...
             STATE_1 = 1,       // State 1 description...
             STATE_2 = 2,       // State 2 description...
             STATE_3 = 3,       // State 3 description...
             STATE_4 = 4,       // State 4 description...
             STATE_5 = 5,       // State 5 description...
             STATE_FINAL = 6,   // State 6 description...
             Reserved1,         // Reserved for future use
             Reserved2,         // Reserved for future use
             Reserved3};        // Reserved for future use

/*********************************************************************************************
 <<<<<<< STATE Function Prototypes
 *********************************************************************************************/

enum states State_Inital_Action();
enum states State_1_Action();
enum states State_2_Action();
enum states State_3_Action();
enum states State_4_Action();
enum states State_5_Action();
enum states State_Final_Action();

/*********************************************************************************************
 <<<<<<< STATE Function Pointer Array
 *********************************************************************************************/
enum states (*StateFunctions[])() = {State_Inital_Action,
                                     State_1_Action,
                                     State_2_Action,
                                     State_3_Action,
                                     State_4_Action,
                                     State_5_Action,
                                     State_Final_Action,
                                     State_Final_Action,     // Catch for future expansion
                                     State_Final_Action,     // Catch for future expansion
                                     State_Final_Action};    // Catch for future expansion

/*********************************************************************************************
 <<<<<<< STATE Variables
 *********************************************************************************************/
enum states CurrentState = STATE_INITAL;      // Keeps track of the current state
enum states LastState = STATE_INITAL;         // State transitions are not always sequential...

/*********************************************************************************************
 <<<<<<< main()
 *********************************************************************************************/
int main(void)
{
    TRISA = 0x00;

    while(1)
    {
        do
        {
            LATA = LastState = CurrentState;
            CurrentState = StateFunctions[CurrentState]();

        } while(CurrentState != STATE_FINAL);

        CurrentState=State_Final_Action();
    }

    return(0);
}


/*********************************************************************************************
 <<<<<<< delay()
 * Makes the trivial state functions take some time - it will show up better on DMCI this way
 *********************************************************************************************/
void delay(void)
{
    long i, j;

    for(i = 0; i < SUFFICIENT_TIME; i++)
    {
        for(j = 0; j < DMCI_STEP_WIDTH; j++)
        {
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
        CurrentState = CurrentState;    // So DMCI had a continuous update
    }
}

/*********************************************************************************************
 <<<<<<< State_Inital_Action()
 *********************************************************************************************/
enum states State_Inital_Action()
{
    delay();                // In a real application, we'd perform some task here...
    return(STATE_1);
}

/*********************************************************************************************
 <<<<<<< State_1_Action()
 *********************************************************************************************/
enum states State_1_Action()
{
    delay();                // In a real application, we'd perform some task here...
    return(STATE_2);
}

/*********************************************************************************************
 <<<<<<< State_2_Action()
 *********************************************************************************************/
enum states State_2_Action()
{
    delay();                // In a real application, we'd perform some task here...
    return(STATE_3);
}

/*********************************************************************************************
 <<<<<<< State_3_Action() : === BAD STUFF HERE ===
 * Don't worry too much about what the code is doing here, the problem is in the return
 * statement at the end of the function.  The code above it is designed to make the bug
 * appear only occasionally.  Most of the time, a value of (STATE_4 * 1) is returned, but
 * sometimes a value of (STATE_4 * 2) is returned instead - this is bad...
 *********************************************************************************************/
enum states State_3_Action()
{
//====== BUG SUPPORT CODE =====================================================================
    int foo;
    static int state_loop_count = 0;

    if((state_loop_count++ & 0x0F) == 13)   // Once every 16 iterations of state loop
        foo = 2;                            // multiply return value by 2,
    else
        foo = 1;                            // but rest of time just multiply return value by 1
//====== END BUG SUPPORT CODE =================================================================

    delay();                    // In a real application, we'd perform some task here...
    return(STATE_4 * foo);      // Here's where the bug manifests itself from time to time...
}

/*********************************************************************************************
 <<<<<<< State_4_Action()
 *********************************************************************************************/
enum states State_4_Action()
{
    delay();                // In a real application, we'd perform some task here...
    return(STATE_5);
}

/*********************************************************************************************
 <<<<<<< State_5_Action()
 *********************************************************************************************/
enum states State_5_Action()
{
    delay();                // In a real application, we'd perform some task here...
    return(STATE_FINAL);
}

/*********************************************************************************************
 <<<<<<< State_Final_Action()
 *********************************************************************************************/
enum states State_Final_Action()
{
    delay();                // In a real application, we'd perform some task here...
    return(STATE_INITAL);
}


