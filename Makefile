csubatch: csubatch.c commandline_parser.c scheduler.c dispatcher.c jobQueue.c performance.c
		gcc -o csubatch csubatch.c commandline_parser.c scheduler.c dispatcher.c jobQueue.c performance.c -lpthread
