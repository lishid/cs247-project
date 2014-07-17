#include "Subject.h"
#include "Observer.h"

void Subject::subscribe(Observer *observer) {
	observers_.insert(observer);
}

void Subject::unsubscribe(Observer *observer) {
	observers_.erase(observer);
}

void Subject::notify() {
	for (Observers::iterator i = observers_.begin(); i != observers_.end(); ++i){
		(*i)->update();
	}
}
