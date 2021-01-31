# Git Nocheckin - Pre-Commit hook
Inspired by popular svn hook.



This hook scans staged files for ```nocheckin``` character sequence and blocks the commit if it's found.  
In other words - if after commiting one of the files affected by the commit will contain ```nocheckin``` then this hook will complain.  


You can bypass it with: ```git commit --no-verify```.  


To install this hook globally for git you can download ```pre-commit``` executable from here:  
https://github.com/fda0/git_nocheckin_hook/releases

And set global git hooks path with:  
```git config --global core.hooksPath path/to/pre-commit-directory/```


It wasn't designed to be everything for everybody - all I can say is - __it works on my machine__ with stage (git add) and commit workflow.

