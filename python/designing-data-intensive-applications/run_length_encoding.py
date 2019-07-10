# This program will take in a list of rows in which a particular column
# value will appear and translate it into a run-length encoding.

from collections import namedtuple
import sys

RunSpec = namedtuple('RunSpec', ['start', 'length'])

class RunLengthEncoding():
    def __init__(self):
        self.specs = []

    def _find_prev_offset(self, offset):
        # Find the one before this one
        prevIndex = -1
        for spec in self.specs:
            if spec.start > offset:
                return prevIndex
            prevIndex += 1
        return prevIndex

    def _insert_at_head(self, offset):
        if not self.specs or self.specs[0].start > offset + 1:
            self.specs.insert(0, RunSpec(offset, 1))
            return

        # This case lengthens the first extent
        # Need to make a new run spec since namedTuples are immutable.
        prevSpec = self.specs[0]
        self.specs[0] = RunSpec(prevSpec.start - 1, prevSpec.length + 1)


    def _maybe_consolidate(self, prevIndex):
        if prevIndex == (len(self.specs) - 1):
            return
        prevSpec = self.specs[prevIndex]
        nextSpec = self.specs[prevIndex + 1]

        if (prevSpec.start + prevSpec.length) != nextSpec.start:
            return

        newSpec = RunSpec(prevSpec.start, (prevSpec.length + nextSpec.length))
        self.specs[prevIndex] = newSpec
        self.specs.pop(prevIndex + 1)

    def _insert_in_or_after(self, offset, prevIndex):
        # Is this included already? (we are assuming that the previous run
        # start is less than the offset)
        prevSpec = self.specs[prevIndex]
        if offset < (prevSpec.start + prevSpec.length - 1):
            return
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


    def __str__(self):
        specStrs = []
        for spec in self.specs:
            specStrs.append('start: {}, length: {}'.format(spec.start, spec.length))
        return '\n'.join(specStrs)


encoding = RunLengthEncoding()
encoding.add(8)
print encoding
print '-------------------------------------'
encoding.add(2)
print encoding
print '-------------------------------------'
encoding.add(7)
print encoding
print '-------------------------------------'
encoding.add(4)
print encoding
print '-------------------------------------'
encoding.add(3)
print encoding
