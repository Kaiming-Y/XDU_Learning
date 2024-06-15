# 2 Simple Scheduling Problem

def calculate_average_completion_time(jobs):
    sorted_jobs = sorted(jobs)

    completion_time = sorted_jobs

    for i in range(1, len(jobs)):
        completion_time[i] += completion_time[i - 1]

    average_completion_time = sum(completion_time) / len(jobs)

    return average_completion_time, sorted_jobs


jobs = [15, 8, 3, 10]

average_time, job_order = calculate_average_completion_time(jobs)
print(average_time, job_order)
