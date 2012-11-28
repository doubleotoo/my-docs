# Jenkins

## Groovy

### Get One Job by Name

```bash
def project = hudson.model.Hudson.instance.getJob(name)
```

### Get Downstream Jobs

```bash
def project = hudson.model.Hudson.instance.getJob(name)
def downstreamProjects = project.getDownstreamProjects()
```

### List Jobs in View

```bash
// Here, "Integration" is the view name
["Integration"].each() { viewName ->

  allJobs = new ArrayList()

  hudson.model.Hudson.instance.getView(viewName).items.each() { job ->
      jobName = job.getName()
      println(jobName)
  }
}
```