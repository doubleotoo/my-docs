# Jenkins

## Groovy

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