/*
** live.c for corewar in /home/ecormi_p//crw-vm-asm/vm/vm_funcs
** 
** Made by pierre ecormier
** Login   <ecormi_p@epitech.net>
** 
** Started on  Tue Feb 21 15:33:22 2012 pierre ecormier
** Last update Sat Mar 24 15:46:07 2012 pierre ecormier
*/

#include	<stdio.h>
#include	"op.h"
#include	"corewar.h"
#include	"vm_funcs.h"

void		add(t_arena *arena, t_champ *champ, char type[4], int argv[4])
{
  if (!REG_VALID(argv[0]) || !REG_VALID(argv[1]))
    return;
  printf("add (r%d=%d + r%d=%d -> ", argv[0], champ->r[argv[0]], argv[1], champ->r[argv[1]]);
  champ->r[argv[2]] = champ->r[argv[0]] + champ->r[argv[1]];
  champ->carry = (champ->r[argv[2]] == 0);
  printf("r%d=%d) carry=%d\n", argv[2], champ->r[argv[2]], champ->carry);
  arena = arena;
  type = type;
}

void		sub(t_arena *arena, t_champ *champ, char type[4], int argv[4])
{
  if (!REG_VALID(argv[0]) || !REG_VALID(argv[1]))
    return;
  printf("sub (r%d=%d - r%d=%d -> ", argv[0], champ->r[argv[0]], argv[1], champ->r[argv[1]]);
  champ->r[argv[2]] = champ->r[argv[0]] - champ->r[argv[1]];
  champ->carry = (champ->r[argv[2]] == 0);
  printf("r%d=%d) carry=%d\n", argv[2], champ->r[argv[2]], champ->carry);
  arena = arena;
  type = type;
}

void		and(t_arena *arena, t_champ *champ, char type[4], int argv[4])
{
  if (!REG_VALID(argv[0]) || !REG_VALID(argv[1]))
    return;
  printf("and (r%d=%d & r%d=%d -> ", argv[0], champ->r[argv[0]], argv[1], champ->r[argv[1]]);
  champ->r[argv[2]] = champ->r[argv[0]] & champ->r[argv[1]];
  champ->carry = (champ->r[argv[2]] == 0);
  printf("r%d=%d) carry=%d\n", argv[2], champ->r[argv[2]], champ->carry);
  arena = arena;
  type = type;
}

void		or(t_arena *arena, t_champ *champ, char type[4], int argv[4])
{
  if (!REG_VALID(argv[0]) || !REG_VALID(argv[1]))
    return;
  printf("or (r%d=%d | r%d=%d -> ", argv[0], champ->r[argv[0]], argv[1], champ->r[argv[1]]);
  champ->r[argv[2]] = champ->r[argv[0]] | champ->r[argv[1]];
  champ->carry = (champ->r[argv[2]] == 0);
  printf("r%d=%d) carry=%d\n", argv[2], champ->r[argv[2]], champ->carry);
  arena = arena;
  type = type;
}

void		xor(t_arena *arena, t_champ *champ, char type[4], int argv[4])
{
  if (!REG_VALID(argv[0]) || !REG_VALID(argv[1]))
    return;
  printf("xor (r%d=%d ^ r%d=%d -> ", argv[0], champ->r[argv[0]], argv[1], champ->r[argv[1]]);
  champ->r[argv[2]] = champ->r[argv[0]] ^ champ->r[argv[1]];
  champ->carry = (champ->r[argv[2]] == 0);
  printf("r%d=%d) carry=%d\n", argv[2], champ->r[argv[2]], champ->carry);
  arena = arena;
  type = type;
}
