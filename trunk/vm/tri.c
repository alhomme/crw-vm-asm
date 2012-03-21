/*
** tri.c for tri in /home/kyndt/crw-vm-asm/vm
** 
** Made by clovis kyndt
** Login   <kyndt_c@epitech.net>
** 
** Started on  Thu Mar 15 13:48:52 2012 clovis kyndt
** Last update Wed Mar 21 16:31:55 2012 guillaume boell
*/

#include        "op.h"
#include        "corewar.h"
#include        "vm_funcs.h"

char            select_oct(char tb[], char c)
{
  int           i;
  int           n;
  char		arg;
  char          d1;
  char          d2;

  i = 7;
  n = 0;
  arg = 0;
  while (i >= 0)
    {
      d1 = !!(c & (1 << i));
      i--;
      d2 = !!(c & (1 << i));
      tb[n] = d1 * 2 + d2;
      if (tb[n++] > 0)
	arg++;
      i--;
    }
  tb[n] = '\0';
  return (arg);
}

void		print_my_arg(char *map, int *i, int arg[], char nb)
{
  int		n;

  n  = 0;
  while (nb > 0 && n < 4)
    {
      *i = (*i + 1) % MEM_SIZE;
      arg[n] = map[*i];
      nb--;
    }
  arg[n] = '\0';
}

int		dedi_no_tab(t_champ *champ, t_arena *arena, int *i, char index, void (*act_fct[16])(t_arena *arena, t_champ *champ, char type[4], int argv[4]))
{
  int		arg[4];
  char		type[4];
  int		nb;
  int		ptr_i;

  ptr_i = *i + 1;
  type[0] = '\0';
  if (index)
    {
      nb = (arena->map)[ptr_i % MEM_SIZE];
      nb = select_oct(type, nb);
      print_my_arg(arena->map, &ptr_i, arg, nb);
    }
  else
    print_my_arg(arena->map, &ptr_i, arg, 1);
  champ->pc = ptr_i;
  nb = (arena->map)[*i] - 1;
  printf("nb:%d champ->pc(old):%d champ->pc(new):%d\n", nb, *i, champ->pc);
  if (nb < 16 && nb > 0)
    (act_fct[nb])(arena, champ, type, arg);
  return (0);
}

void		init_time_tab(int time_tab[])
{
  time_tab[0] = 10;
  time_tab[1] = 5;
  time_tab[2] = 5;
  time_tab[3] = 10;
  time_tab[4] = 10;
  time_tab[5] = 6;
  time_tab[6] = 6;
  time_tab[7] = 6;
  time_tab[8] = 20;
  time_tab[9] = 25;
  time_tab[10] = 25;
  time_tab[11] = 800;
  time_tab[12] = 10;
  time_tab[13] = 50;
  time_tab[14] = 1000;
  time_tab[15] = 2;
}

int		time_action(char c)
{
  int		time_tab[16];
  int		i;

  i = c;
  init_time_tab(time_tab);
  if (c >= 0 && c < 16)
    return (time_tab[i]);
  return (0);
}

int		read_arg(t_arena *arena, void (*act_fct[16])(t_arena *arena, t_champ *champ, char type[4], int argv[4]), int cycle)
{
  int		i;
  t_champ	*champ;
  char		*mem;
  char		type;
  int		time_act;

  champ = arena->champs;
  mem = arena->map;
  while (champ != NULL)
    {
      i = champ->pc;
      type = 1;
      if (mem[i] == LIVE || mem[i] == ZJMP || mem[i] == FORK || mem[i] == LFORK)
	type = 0;
      time_act = time_action(mem[i]);
     if ((champ->cycle + time_act) <= cycle)
	{
	  dedi_no_tab(champ, arena, &i, type, act_fct);
	  champ->cycle = cycle;
	}
      champ = champ->next;
    }
  return (0);
}


void		init_fct_tab(void  (*act_fct[])(t_arena *arena, t_champ *champ, char type[4], int argv[4]))
{
  act_fct[0] = live;
  act_fct[1] = ld;
  act_fct[2] = st;
  act_fct[3] = add;
  act_fct[4] = sub;
  act_fct[5] = and;
  act_fct[6] = or;
  act_fct[7] = xor;
  act_fct[8] = zjmp;
  act_fct[9] = ldi;
  act_fct[10] = sti;
  act_fct[11] = fork;
  act_fct[12] = lld;
  act_fct[13] = lldi;
  act_fct[14] = lfork;
  act_fct[15] = aff;
}

int		champ_count(t_champ *champ)
{
  int		i;
  t_champ	*tmp;

  i = 0;
  tmp = champ;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

t_champ		*kill_champ(t_champ *champs)
{
  t_champ	*tmp;
  t_champ	*tmp2;

  tmp = champs;
  if (tmp->last_live == 0)
    {
      tmp = tmp->next;
      free(champs);
      return (tmp);
    }
  tmp2 = tmp;
  tmp = tmp->next;
  while (tmp != NULL)
    {
      if (tmp->last_live == 0)
	{
	  tmp2->next = tmp->next;
	  free(tmp);
	  return (champs);
	}
      tmp = tmp->next;
    }
  return (tmp);
}

void		apply_search(t_arena *arena, t_args_events *args)
{
  int		cycle;
  int		cycle_m;
  void		(*act_fct[16])(t_arena *arena, t_champ *champ, char type[4], int argv[4]);

  init_fct_tab(act_fct);
  cycle_m = arena->cycle_to_die;
  while (champ_count(arena->champs) > 1)
    {
      cycle = 0;
      arena->nb_live = 0;
      while (cycle < arena->cycle_to_die && arena->nb_live < NBR_LIVE)
	{
	  do_refresh(args);
	  read_arg(arena, act_fct, cycle);
	  cycle++;
	}
      if (arena->nb_live >= NBR_LIVE)
	arena->cycle_to_die -= CYCLE_DELTA;
      arena->champs = kill_champ(arena->champs);
    }
  puts("END");
}
