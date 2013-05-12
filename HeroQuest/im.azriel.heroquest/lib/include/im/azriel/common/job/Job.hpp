/*
 * Job.hpp
 *
 *  Created on: 28/04/2013
 *      Author: azriel
 */

#ifndef __IM_AZRIEL_COMMON_JOB__JOB_H_
#define __IM_AZRIEL_COMMON_JOB__JOB_H_

#include <string>

#include "im/azriel/common/imports/SdlImports.h"
#include "im/azriel/common/threading/Thread.h"
#include "im/azriel/common/threading/Runnable.h"

using namespace std;
using namespace im::azriel::common::threading;

namespace im {
namespace azriel {
namespace common {
namespace job {

template<class T = void>
class Job {
protected:
	static const string DEFAULT_NOT_STARTED_STATUS_MESSAGE;
	static const string DEFAULT_LOADING_STATUS_MESSAGE;
	static const string DEFAULT_COMPLETE_STATUS_MESSAGE;

private:
	/**
	 * Thread that runs this job.
	 */
	Thread* thread;
	/**
	 * Runnable that does the work.
	 */
	Runnable* jobRunner;
	/**
	 * Lock for the status of this job.
	 */
	SDL_mutex* const jobStatusLock;
	/**
	 * The status for this job.
	 */
	string statusMessage;
	/**
	 * Lock for the status message of this job.
	 */
	SDL_mutex* const statusMessageLock;

protected:
	/**
	 * Whether this job is running.
	 */
	bool running;
	/**
	 * Whether this job is completed.
	 */
	bool complete;
	/**
	 * The value returned by this job when it ends.
	 */
	T returnValue;

public:
	Job();
	virtual ~Job();
	/**
	 * Get the return value of this job
	 *
	 * @return the return value
	 */
	T getReturnValue() const;
	/**
	 * Gets the current status message for this job.
	 *
	 * @return the current status message for this job
	 */
	const string getStatusMessage() const;
	/**
	 * Whether this job is complete. A job must be complete before the {@Link #getReturnValue} function is called.
	 *
	 * @return {@code true} if this job is complete, {@code false} otherwise
	 */
	const bool isComplete() const;
	/**
	 * Whether this job is running. This will be true if the job is started but is not yet complete.
	 *
	 * @return {@code true} if this job is running, {@code false} otherwise
	 */
	const bool isRunning() const;
	/**
	 * Starts this job. This should only be called once. When #isComplete() returns {@code true}, then the return value
	 * can be retrieved using #getReturnValue();
	 */
	void start();

protected:
	/**
	 * Method to be implemented by subclasses that is the actual implementation of the job.
	 *
	 * @return the return value for this job
	 */
	virtual T doWork() = 0;
	/**
	 * Sets the status message for this job. This must be used by subclasses to set the status message as it enforces
	 * synchronization when accessing the status message.
	 *
	 * @param message the new status message
	 */
	void setStatusMessage(const string message);

private:
	/**
	 * Runs this job, and sets the return value. This is only used by the JobRunner.
	 */
	void runJob();
};

template<class T>
const string Job<T>::DEFAULT_NOT_STARTED_STATUS_MESSAGE = "Not started";
template<class T>
const string Job<T>::DEFAULT_LOADING_STATUS_MESSAGE = "Loading";
template<class T>
const string Job<T>::DEFAULT_COMPLETE_STATUS_MESSAGE = "Complete";

template<class T>
Job<T>::Job() :
				thread(nullptr),
				jobRunner(nullptr),
				jobStatusLock(SDL_CreateMutex()),
				statusMessage(DEFAULT_NOT_STARTED_STATUS_MESSAGE),
				statusMessageLock(SDL_CreateMutex()),
				running(false),
				complete(false),
				returnValue(nullptr) {
}

template<class T>
Job<T>::~Job() {
	delete this->thread;
	SDL_DestroyMutex(this->jobStatusLock);
	SDL_DestroyMutex(this->statusMessageLock);
}

template<class T>
T Job<T>::getReturnValue() const {
	return this->returnValue;
}

template<class T>
const string Job<T>::getStatusMessage() const {
	SDL_mutexP(this->statusMessageLock);
	const string message(this->statusMessage);
	SDL_mutexV(this->statusMessageLock);
	return message;
}

template<class T>
const bool Job<T>::isComplete() const {
	SDL_mutexP(this->jobStatusLock);
	const bool retValue = this->complete;
	SDL_mutexV(this->jobStatusLock);
	return retValue;
}

template<class T>
const bool Job<T>::isRunning() const {
	SDL_mutexP(this->jobStatusLock);
	const bool retValue = this->running;
	SDL_mutexV(this->jobStatusLock);
	return retValue;
}

template<class T>
void Job<T>::start() {
	SDL_mutexP(this->jobStatusLock);
	this->running = true;
	if (this->thread == nullptr) {

		class JobRunner: public Runnable {
		private:
			Job* const job;
		public:
			JobRunner(Job* job) :
					job(job) {
			}
			virtual ~JobRunner() {
			}
			const int run() {
				this->job->runJob();
				return 0;
			}
		} runner = { this };
		this->jobRunner = runner;

		this->thread = new Thread(this->jobRunner);
		this->thread->start();
	}
	SDL_mutexV(this->jobStatusLock);
}

template<class T>
void Job<T>::runJob() {
	this->returnValue = doWork();
	SDL_mutexP(this->jobStatusLock);
	this->running = false;
	this->complete = true;
	SDL_mutexV(this->jobStatusLock);
}

template<class T>
void Job<T>::setStatusMessage(const string message) {
	SDL_mutexP(this->statusMessageLock);
	this->statusMessage = message;
	SDL_mutexV(this->statusMessageLock);
}

} /* namespace job */
} /* namespace common */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_COMMON_JOB__JOB_H_ */
