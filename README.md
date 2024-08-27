# 42-stud-microshell

this code are adapted for pass 42 exam subject microshell with a bit of security (not really necessary for validate it)

	- no dynamic allocation
	- check failure function
	
memo for dup & close
====================

	function 
		exec :
		
			dup2 fd_tmp  , 0
			close fd_tmp
			execve
	
		exec-fork :
		
			child :
				execve
				
			parent :
				close  fd_tmp
				waitpid 
				dup fd_tmp  0
				
		exec-pipe :
		
			child :
				dup2 fd[1] , 1
				close fd[1]
				close fd[0]
				execve
				
			parent :
				close fd[1]
				close fd_tmp
				fd_tmp = fd[0]
		
		main 
			dup fd _tmp, 0
			....
			close fd_tmp
				
			
				
		

	
