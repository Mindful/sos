To generate the executeable run 'make'


To run the program run './main'


the program defaults to simulating 4 processors with 5 ticks
  between prompts. The settings for this are represented by the
  arguments to the scheduler constructor in project_1.cpp
  
  The program prompts you for jobs. First it asks if you want to add a job.
  'y' will lead to the next prompts:
    'Please enter a job description' - Enter the name of the job, for
      the report later.
    'Please enter a number of required processors' - Enter the number
      of processors this job will required. if the number is larger
      than the total number of processors, the job will be rejected.
    'Please enter a number of ticks' - Enter the number of ticks on each
      processor this job will take to complete. Jobs with ticks < 0
      will be rejected.
  
  'n' will run the simulation for 5 ticks and return to the prompt,
    after printing a report about the current state of the wait and run queues.
    
  'exit' exits the program.