#include "plumber.h"

int sporth_tdiv(sporth_stack *stack, void *ud)
{
    plumber_data *pd = ud;
    SPFLOAT trigger;
    SPFLOAT out;
    SPFLOAT num;
    sp_tdiv *tdiv;

    switch(pd->mode) {
        case PLUMBER_CREATE:

#ifdef DEBUG_MODE
            fprintf(stderr, "tdiv: Creating\n");
#endif

            sp_tdiv_create(&tdiv);
            plumber_add_ugen(pd, SPORTH_TDIV, tdiv);
            if(sporth_check_args(stack, "f") != SPORTH_OK) {
                fprintf(stderr,"Not enough arguments for tdiv\n");
                stack->error++;
                return PLUMBER_NOTOK;
            }
            num = sporth_stack_pop_float(stack);
            trigger = sporth_stack_pop_float(stack);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_INIT:

#ifdef DEBUG_MODE
            fprintf(stderr, "tdiv: Initialising\n");
#endif

            num = sporth_stack_pop_float(stack);
            trigger = sporth_stack_pop_float(stack);
            tdiv = pd->last->ud;
            sp_tdiv_init(pd->sp, tdiv);
            sporth_stack_push_float(stack, 0);
            break;
        case PLUMBER_COMPUTE:
            num = sporth_stack_pop_float(stack);
            trigger = sporth_stack_pop_float(stack);
            tdiv = pd->last->ud;
            tdiv->num = num;
            sp_tdiv_compute(pd->sp, tdiv, &trigger, &out);
            sporth_stack_push_float(stack, out);
            break;
        case PLUMBER_DESTROY:
            tdiv = pd->last->ud;
            sp_tdiv_destroy(&tdiv);
            break;
        default:
            fprintf(stderr, "tdiv: Uknown mode!\n");
            break;
    }
    return PLUMBER_OK;
}
