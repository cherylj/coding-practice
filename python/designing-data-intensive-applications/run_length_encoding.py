# This program will take in a list of rows in which a particular column
# value will appear and translate it into a run-length encoding.

from collections import namedtuple
import sys

RunSpec = namedtuple('RunSpec', ['start', 'length'])

class RunLengthEncoding():
    def __init__(self):
        self.specs = []

    def _find_prev_offset(self, offset):
        ''' This will return the index of the run spec that might
        contain the offset specified (based on the 'start' value).  If
        the first run spec starts at a larger offset, -1 is returned
        '''
        prevIndex = -1
        for spec in self.specs:
            if spec.start > offset:
                return prevIndex
            prevIndex += 1
        return prevIndex

    def _insert_at_head(self, offset):
        # If the list is empty, or we won't join with the first
        # run spec, we will insert a new run spec at the beginning.
        if not self.specs or self.specs[0].start > offset + 1:
            self.specs.insert(0, RunSpec(offset, 1))
            return

        # This case lengthens the first extent (by starting at one offset less)
        # We need to make a new run spec since namedTuples are immutable.
        prevSpec = self.specs[0]
        self.specs[0] = RunSpec(prevSpec.start - 1, prevSpec.length + 1)

    def _maybe_consolidate(self, prevIndex):
        ''' This will merge two run specs, prevIndex and prevIndex + 1, if
        they are eligible
        '''

        # Is this the last run spec?  If so, nothing to do
        if prevIndex == (len(self.specs) - 1):
            return

        prevSpec = self.specs[prevIndex]
        nextSpec = self.specs[prevIndex + 1]

        # Is the last offset in prevSpec not right before the start of nextSpec?
        if (prevSpec.start + prevSpec.length) != nextSpec.start:
            return

        # The two run specs collide, so let's merge them!
        newSpec = RunSpec(prevSpec.start, (prevSpec.length + nextSpec.length))
        self.specs[prevIndex] = newSpec
        self.specs.pop(prevIndex + 1)

    def _insert_in_or_after(self, offset, prevIndex):
        prevSpec = self.specs[prevIndex]

        # Is this included already? (we are assuming that the previous run
        # start is less than the offset)
        if offset < (prevSpec.start + prevSpec.length):
            return

        # Does this just extend the prevSpec by 1?  If it does, we may need to
        # merge prevIndex and prevIndex + 1.
        if offset == (prevSpec.start + prevSpec.length):
            self.specs[prevIndex] = RunSpec(prevSpec.start, prevSpec.length + 1)
            self._maybe_consolidate(prevIndex)
            return

        # Do we need to add a new one at the end?
        if prevIndex == (len(self.specs) - 1):
            self.specs.append(RunSpec(offset, 1))
            return

        # Does this belong to the next run?
        nextSpec = self.specs[prevIndex + 1]
        if offset == nextSpec.start - 1:
            self.specs[prevIndex + 1] = RunSpec(offset, nextSpec.length + 1)
            return

        # Otherwise, this is a new run between the prevIndex and prevIndex + 1
        self.specs.insert(prevIndex + 1, RunSpec(offset, 1))

    def add(self, offset):
        if not self.specs:
            self.specs.append(RunSpec(offset, 1))
            return
        prevIndex = self._find_prev_offset(offset)

        if prevIndex == -1:
            self._insert_at_head(offset)
            return
        self._insert_in_or_after(offset, prevIndex)

    def contains(self, offset):
        prevIndex = self._find_prev_offset(offset)
        if prevIndex == -1:
            return False

        prevSpec = self.specs[prevIndex]
        return (offset < (prevSpec.start + prevSpec.length))

    def __str__(self):
        specStrs = []
        for spec in self.specs:
            specStrs.append('start: {}, length: {}'.format(spec.start, spec.length))
        return '\n'.join(specStrs)
