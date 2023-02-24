#include "executor.h"

int	ft_chk_builtins(char *cmd)
{
	if (ft_strncmpp(cmd, "echo", 4) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "cd", 2) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "export", 6) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "unset", 5) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "env", 3) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "exit", 4) == 0)
		return (0);
	else if (ft_strncmpp(cmd, "$?", 2) == 0)
		return (0);
	return (1);
}