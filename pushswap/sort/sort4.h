#ifndef SORT4_H
# define SORT4_H

# include "../utils/operations.h"
# include "../utils/operations2.h"
# include "../utils/utils.h"
# include "../utils/utils2.h"
# include "../utils/utils3.h"
# include "./sort3.h"

int		sort4wrapper(t_stack *stack_a, t_stack *stack_b, int *numberofop);
void	find4_numbers(t_node *head, t_element4 *element4, int size);
void	sort4_al(t_stack *stack_a, t_stack *stack_b, int *numberofop,
			t_element4 *element4);
void	sort_4_top3(t_element4 *element4, t_stack *stack_a, int *numberofop);

#endif
