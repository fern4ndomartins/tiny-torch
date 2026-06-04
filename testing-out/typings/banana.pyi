"""
pybind11 example module
"""
from __future__ import annotations
import typing
__all__: list[str] = ['add', 'subtract']
def add(a: typing.SupportsInt | typing.SupportsIndex, b: typing.SupportsInt | typing.SupportsIndex) -> int:
    """
    A function that adds two numbers
    """
def subtract(a: typing.SupportsInt | typing.SupportsIndex, b: typing.SupportsInt | typing.SupportsIndex) -> int:
    """
    A function that subtracts two numbers
    """
