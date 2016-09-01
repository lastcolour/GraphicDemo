import os
import sys

from unittest import TestCase
from unittest import TextTestRunner
from unittest import makeSuite

try:
  from initter import Initializer
except ImportError:
  sys.path.append(
    os.path.abspath(os.path.abspath(__file__) + "/../.."))
  try:
    from initter import Initializer
  except ImportError:
    print >> sys.stderr, "[Fatal Error] Can't import test class: ", sys.exc_info()[1]
    sys.exit(1)

TMP_DIR = os.path.abspath(os.path.abspath(__file__) + "/../tmp")

class TestInitterCase(TestCase):

  def setUp(self):
    if os.path.exists(TMP_DIR):
      self.tearDown()
    try:
      os.mkdir(TMP_DIR)
    except:
      print >> sys.stderr, "[Fatal Error] Can't create tmp dir for test run"
      print >> sys.stderr, "[Fatal Error] Problem", sys.exc_info()[1]
      self.fail("Can't set up test")

  def tearDown(self):
    if not os.path.exists(TMP_DIR):
      self.fail("After test is absent required dir")
    try:
      os.rmdir(TMP_DIR)
    except:
      print >> sys.stderr, "[Fatal Error] Can't delete tmp dir after test run"
      print >> sys.stderr, "[Fatal Error] Problem", sys.exc_info()[1]
      self.fail("Can't tear down test")

  def testValidConstruction(self):
    """ Validate construction with valid params """
    tPath = {"root": TMP_DIR}
    try:
      tInitObj = Initializer(tPath)
    except:
      self.fail("Cant create instance of Initializer")

  def testInvalidConstruction(self):
    """ Validate construction with invalid params """
    try:
      from hashlib import sha1
      tPath = {"root": sha1("?").hexdigest()}

      Initializer(tPath)
    except:
      print sys.exc_info()[1]
    else:
      self.fail("No exception occurs with invalid params")


if __name__ == "__main__":
  tSuite = makeSuite(TestInitterCase)
  TextTestRunner().run(tSuite)