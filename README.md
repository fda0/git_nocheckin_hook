# Git Nocheckin - Pre-Commit hook
Inspired by popular svn hook.



This hook scans staged changes for ```nocheckin``` character sequence.  
You can bypass this hook with ```git commit --no-verify```.



To install this hook globally for git you can download ```pre-commit``` executable from here:  
https://github.com/fda0/git_nocheckin_hook/releases

And set global git hooks path with:  
```git config --global core.hooksPath path/to/pre-commit```

