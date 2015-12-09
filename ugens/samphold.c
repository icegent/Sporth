#include "plumber.h"

int sporth_samphold(sporth_stack *stack, void *ud)
{
    plumber_data *pd = ud;
    SPFLOAT trig;
    SPFLOAT input;
    SPFLOAT out;
    sp_samphold *samphold;

    switch(pd->mode) {
        case PLUMBER_CREATE:

#ifdef DEBUG_MODE
            fprintf(stderr, "samphold: Creating\n");
#endif

            sp_samphold_create(&samphold);
            plumber_add_ugen(pd, SPORTH_SAMPHOLD, samphold);
            break;
        case PLUMBER_INIT:

#ifdef DEBUG_MODE
            fprintf(stderr, "samphold: Initialising\n");
#endif

            if(sporth_check_args(stack, "ff") != SPORTH_OK) {
                fprintf(stderr,"Not enough arguments for samphold\n");
                stack->error++;
                return PLUMBER_NOTOK;
            }
            trig = sporth_stack_pop_float(stack);
            input = sporth_stack_pop_float(stack);
            samphold = pd->last->ud;
            sp_samphold_init(pd->sp, samphold);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_COMPUTE:
            if(sporth_check_args(stack, "ff") != SPORTH_OK) {
                fprintf(stderr,"Not enough arguments for samphold\n");
                stack->error++;
                return PLUMBER_NOTOK;
            }
            trig = sporth_stack_pop_float(stack);
            input = sporth_stack_pop_float(stack);
            samphold = pd->last->ud;
            sp_samphold_compute(pd->sp, samphold, &trig, &input, &out);
            sporth_stack_push_float(stack, out);
            break;
        case PLUMBER_DESTROY:
            samphold = pd->last->ud;
            sp_samphold_destroy(&samphold);
            break;
        default:
            fprintf(stderr, "samphold: Uknown mode!\n");
            break;
    }
    return PLUMBER_OK;
}
