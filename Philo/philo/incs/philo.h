#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define DIED 0
# define SLEEP 1
# define THINK 2
# define EAT 3
# define TAKE 4

typedef struct	s_parsing
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			philo_must_eat;
}				t_parsing;

typedef struct	s_main
{
	t_parsing		data;
	pthread_mutex_t	write;
	pthread_mutex_t	meal_check;
	struct s_philo	*philo;
	long int		first_time;
	int				stop;
	
}				t_main;

typedef struct s_philo
{
	t_main			*main;
	pthread_mutex_t	fork;
	pthread_mutex_t	*prev_fork;
	long int		last_time;
	int				id;
	int				alive;
	int				sleep;
	int				eat;
	int				think;
	int				nb_ate;
}				t_philo;

void		ft_bzero(void *s, size_t n);
int			parsing(int ac, char **av, t_main *main);
int			initialization(t_main *main);

void		start_simulation(t_main *main, t_philo *philo, pthread_t *threads);
void		*run_simulation(void *data);

void		display_action(t_philo *philo, int action);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_die(t_philo *philo);

void		ft_take_fork(t_philo *philo);
void		ft_drop_fork(t_philo *philo);

long int	ft_get_time(void);
void		better_usleep(long int time, t_philo *philo);

void		quit(t_philo *philo, pthread_t *threads, int j);
#endif