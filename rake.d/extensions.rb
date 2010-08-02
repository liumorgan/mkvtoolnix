class NilClass
  def to_bool
    false
  end

  def blank?
    true
  end
end

class String
  def to_bool
    %w{1 true yes}.include? self.downcase
  end

  def blank?
    empty?
  end
end

class TrueClass
  def to_bool
    self
  end
end

class FalseClass
  def to_bool
    self
  end
end
