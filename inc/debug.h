/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:09:09 by gaeudes           #+#    #+#             */
/*   Updated: 2025/09/20 12:29:54 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <time.h>

# define RESET		"[0m"
# define B_BLUE		"[1;34m"
# define BLUE		"[34m"
# define RED		"[31m"
# define B_RED		"[1;31m"
# define GREY		"[30m"
# define GREEN		"[32m"
# define B_GREEN	"[1;32m"
# define B_LYELLOW	"[1;93m"
# define B_MAJENTA	"[1;35m"
# define B_WHITE	"[1;37m"

# define DEBUG_ON

# if defined(DEBUG_ON) && !defined(DEBUG_OFF)

# define BASENAME(string)		(char *)(strrchr(string, '/') ? strrchr(string, '/') + 1 : (char *)string)

# define WAIT_PROMPT		B_MAJENTA "WAIT" B_LYELLOW "[" RESET BLUE "%s" GREY "(" GREEN "%d" GREY ")"  B_LYELLOW "]" RESET " "
# define WAIT_PROMPT_ARGS	BASENAME(__FILE__), __LINE__

#  define WAIT\
	{\
		char	g = 0;\
		fprintf(stderr, WAIT_PROMPT, WAIT_PROMPT_ARGS);\
		while (read(0, &g, 1) == 1 && g != '\n') ;\
	}


# define DEBUG_PROMPT		B_BLUE "%s" GREY "[" GREEN "%d" GREY "]" RESET ":"
# define DEBUG_PROMPT_ARGS	BASENAME(__FILE__), __LINE__ 

#  define DEBUG(s, ...)\
	{\
			fprintf(stderr, DEBUG_PROMPT" "s"\n", DEBUG_PROMPT_ARGS, ##__VA_ARGS__);\
	}

# define DEBUG_TIMER_BUFFER_SIZE	1024

# ifdef DEBUG_INIT
	double	g_debug_time;
	char	g_debug_start_file[DEBUG_TIMER_BUFFER_SIZE];
	int		g_debug_start_line;
	
	static void	__attribute__((constructor))	debug_init_timer(void) {	g_debug_time = 0;	};
# else
	extern double	g_debug_time;
	extern char		g_debug_start_file[DEBUG_TIMER_BUFFER_SIZE];
	extern int		g_debug_start_line;
# endif

__attribute__((always_inline, flatten))
static inline double	debug_clock(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec + ts.tv_nsec / 1e9);
} 

#  define TIMER_START\
	{\
		if (g_debug_time)\
		{\
			fprintf(stderr, DEBUG_END_TIMER_FORMAT, DEBUG_END_TIMER_ARGS);\
		}\
		g_debug_time = debug_clock();\
		strncpy(g_debug_start_file, BASENAME(__FILE__), (sizeof(g_debug_start_file) - 1));\
		g_debug_start_file[(sizeof(g_debug_start_file) - 1)] = 0;\
		g_debug_start_line = __LINE__;\
	};


# define DEBUG_TIMER_FILEFORMAT	RESET BLUE "%s" GREY "(" BLUE "%d" GREY")" RESET
# define DEBUG_TIMER_FILEARGS(MACRO_FILE, MACRO_LINE)		 BASENAME(MACRO_FILE), MACRO_LINE

# define DEBUG_END_TIMER_FORMAT	B_GREEN "Timer" RESET GREY "["\
			DEBUG_TIMER_FILEFORMAT GREY "-"\
			DEBUG_TIMER_FILEFORMAT GREY "]: " GREEN "%lfs\n" RESET

# define DEBUG_END_TIMER_ARGS	DEBUG_TIMER_FILEARGS(g_debug_start_file, g_debug_start_line),\
								DEBUG_TIMER_FILEARGS(__FILE__, __LINE__),\
								((debug_clock() - g_debug_time))

# define TIMER_STEP\
	{\
		if (g_debug_time == 0.0)\
		{\
			fprintf(stderr, B_RED "Timer never started (%s[%d]\n", BASENAME(__FILE__), __LINE__);\
		}\
		else\
		{\
			fprintf(stderr, DEBUG_END_TIMER_FORMAT, DEBUG_END_TIMER_ARGS);\
		}\
	};
# define TIMER_END\
	{\
		TIMER_STEP\
		g_debug_time = 0.0;\
	};

# else
#  define WAIT			{}
#  define DEBUG(s , ...)	{(void)s;}
#  define TIMER_START
#  define TIMER_END
# endif

#endif


