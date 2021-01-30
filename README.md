# Git Nocheckin - Pre-Commit hook
Inspired by popular svn hook.


This hook scans files that have staged changes (you can work around by doing git parkour if you reaaaally want) for ```nocheckin``` sequence.


To install this hook globally for git you can download ```pre-commit``` executable from here:  
LINK

And set global git hooks path with:  
```git config --global core.hooksPath path/to/pre-commit```
