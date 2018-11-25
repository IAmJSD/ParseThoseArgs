from parsethoseargs import ArgParser
import time


class TooSlow(Exception):
  """This dictates that it is too slow."""


def create_test_action(x, y):
  """Creates a test action."""
  print("[ASSERT] {} == {}".format(x, y))
  assert x == y


parser = ArgParser('hello world "this is a test" "lol lots of stuff')

t1 = time.time()

hello = next(parser)
world = next(parser)
this_is_a_test = next(parser)
lol_lots_of_stuff = next(parser)

slow = (time.time() - t1) * 1000

if slow >= 2:
  raise TooSlow("This took {} ms.".format(slow))

create_test_action(hello, "hello")
create_test_action(world, "world")
create_test_action(this_is_a_test, "this is a test")
create_test_action(lol_lots_of_stuff, "lol lots of stuff")
