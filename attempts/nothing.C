#include "prefetcher.h"
#include "mem-sim.h"
#include <stdio.h>

Prefetcher::Prefetcher() { _ready = false;}

bool Prefetcher::hasRequest(u_int32_t cycle) {
  return _ready;
	// return (_ready1 || _ready2);
}

Request Prefetcher::getRequest(u_int32_t cycle) {
  return _nextReq;
}

void Prefetcher::completeRequest(u_int32_t cycle) { 
  _ready = false;
}

void Prefetcher::cpuRequest(Request req) {
}
